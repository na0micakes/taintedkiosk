#include <PR/ultratypes.h>

#include "game/memory.h"
#include "game/segment2.h"
#include "game/segment7.h"
#include "intro_geo.h"
#include "sm64.h"
#include "textures.h"
#include "types.h"
#include "buffers/framebuffers.h"
#include "game/game_init.h"
#include "audio/external.h"

// background types
#define INTRO_BACKGROUND_SUPER_MARIO 0
#define INTRO_BACKGROUND_GAME_OVER 1

struct GraphNodeMore {
    /*0x00*/ struct GraphNode node;
    /*0x14*/ void *todo;
    /*0x18*/ u32 unk18;
};

// intro geo bss
#if defined(VERSION_SH) || defined(VERSION_CN)
static u16 *sFramebuffers[3];
#endif
static s32 sGameOverFrameCounter;
static s32 sGameOverTableIndex;
static s16 sIntroFrameCounter;

/**
 * Geo callback to render the "Super Mario 64" logo on the title screen
 */
Gfx *geo_intro_nintendo_logo(s32 state, struct GraphNode *node, UNUSED void *context) {
    struct GraphNode *graphNode = node;
    Gfx *dl = NULL;
    Gfx *dlIter = NULL;
    Mtx *scaleMat;

    graphNode->flags = (graphNode->flags & 0xFF) | (LAYER_OPAQUE << 8);
    scaleMat = alloc_display_list(sizeof(*scaleMat));
    dl = alloc_display_list(4 * sizeof(*dl));
    dlIter = dl;

    guScale(scaleMat, 1.0f, 1.0f, 1.0f);

    gSPMatrix(dlIter++, scaleMat, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPDisplayList(dlIter++, &intro_seg7_dl_logo);  // draw model
    gSPPopMatrix(dlIter++, G_MTX_MODELVIEW);
    gSPEndDisplayList(dlIter);

    sIntroFrameCounter++;

    return dl;
}

/**
 * Generates a display list for a single background tile
 *
 * @param index            which tile to render (value from 0 to 11)
 * @param backgroundTable  array describing which image to use for each tile (0 denotes a "Super Mario 64" image, and 1 denotes a "Game Over" image)
 */
static Gfx *intro_backdrop_one_image(s32 index, s8 *backgroundTable) {
    // intro screen background display lists for each of four 80x20 textures
    static const Gfx *introBackgroundDlRows[] = { title_screen_bg_dl_0A000130, title_screen_bg_dl_0A000148,
                                                  title_screen_bg_dl_0A000160, title_screen_bg_dl_0A000178 };

    // intro screen background texture X offsets
    static float xCoords[] = {
        0, 80, 160, 240,
        0, 80, 160, 240,
        0, 80, 160, 240,
    };

    // intro screen background texture Y offsets
    static float yCoords[] = {
        160, 160, 160, 160,
        80,  80,  80,  80,
        0,   0,   0,   0,
    };

    // table that points to either the "Super Mario 64" or "Game Over" tables
    static const u8 *const *textureTables[] = { mario_title_texture_table, game_over_texture_table };

    Mtx *mtx = alloc_display_list(sizeof(*mtx));
    Gfx *displayList = alloc_display_list(36 * sizeof(*displayList));
    Gfx *displayListIter = displayList;
    const u8 *const *vIntroBgTable = segmented_to_virtual(textureTables[backgroundTable[index]]);
    s32 i;

    guTranslate(mtx, xCoords[index], yCoords[index], 0.0f);
    gSPMatrix(displayListIter++, mtx, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_PUSH);
    gSPDisplayList(displayListIter++, &title_screen_bg_dl_0A000118);
    for (i = 0; i < 4; i++) {
        gDPLoadTextureBlock(displayListIter++, vIntroBgTable[i], G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0,
                            G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD)
        gSPDisplayList(displayListIter++, introBackgroundDlRows[i]);
    }
    gSPPopMatrix(displayListIter++, G_MTX_MODELVIEW);
    gSPEndDisplayList(displayListIter);
    return displayList;
}

static s8 introBackgroundIndexTable[] = {
    INTRO_BACKGROUND_SUPER_MARIO, INTRO_BACKGROUND_SUPER_MARIO, INTRO_BACKGROUND_SUPER_MARIO,
    INTRO_BACKGROUND_SUPER_MARIO, INTRO_BACKGROUND_SUPER_MARIO, INTRO_BACKGROUND_SUPER_MARIO,
    INTRO_BACKGROUND_SUPER_MARIO, INTRO_BACKGROUND_SUPER_MARIO, INTRO_BACKGROUND_SUPER_MARIO,
    INTRO_BACKGROUND_SUPER_MARIO, INTRO_BACKGROUND_SUPER_MARIO, INTRO_BACKGROUND_SUPER_MARIO,
};

// only one table of indexes listed
static s8 *introBackgroundTables[] = { introBackgroundIndexTable };

/**
 * Geo callback to render the intro background tiles
 */
Gfx *geo_intro_regular_backdrop(s32 state, struct GraphNode *node, UNUSED void *context) {
    struct GraphNodeMore *graphNode = (struct GraphNodeMore *) node;
    s32 index = graphNode->unk18 & 0xff; // TODO: word at offset 0x18 of struct GraphNode (always ends up being 0)
    s8 *backgroundTable = introBackgroundTables[index];
    Gfx *dl = NULL;
    Gfx *dlIter = NULL;
    s32 i;

    if (state == 1) {  // draw
        dl = alloc_display_list(16 * sizeof(*dl));
        dlIter = dl;
        graphNode->node.flags = (graphNode->node.flags & 0xFF) | (LAYER_OPAQUE << 8);
        gSPDisplayList(dlIter++, &dl_proj_mtx_fullscreen);
        gSPDisplayList(dlIter++, &title_screen_bg_dl_0A000100);
        for (i = 0; i < 12; i++) {
            gSPDisplayList(dlIter++, intro_backdrop_one_image(i, backgroundTable));
        }
        gSPDisplayList(dlIter++, &title_screen_bg_dl_0A000190);
        gSPEndDisplayList(dlIter);
    }
    return dl;
}

static s8 gameOverBackgroundTable[] = {
    INTRO_BACKGROUND_GAME_OVER, INTRO_BACKGROUND_GAME_OVER, INTRO_BACKGROUND_GAME_OVER,
    INTRO_BACKGROUND_GAME_OVER, INTRO_BACKGROUND_GAME_OVER, INTRO_BACKGROUND_GAME_OVER,
    INTRO_BACKGROUND_GAME_OVER, INTRO_BACKGROUND_GAME_OVER, INTRO_BACKGROUND_GAME_OVER,
    INTRO_BACKGROUND_GAME_OVER, INTRO_BACKGROUND_GAME_OVER, INTRO_BACKGROUND_GAME_OVER,
};

/**
 * Geo callback to render the Game Over background tiles
 */
Gfx *geo_intro_gameover_backdrop(s32 state, struct GraphNode *node, UNUSED void *context) {
    struct GraphNode *graphNode = node;
    Gfx *dl = NULL;
    Gfx *dlIter = NULL;
    s32 j;
    s32 i;

    if (state != 1) {  // reset
        sGameOverFrameCounter = 0;
        sGameOverTableIndex = -2;
        for (i = 0; i < ARRAY_COUNT(gameOverBackgroundTable); i++) {
            gameOverBackgroundTable[i] = INTRO_BACKGROUND_GAME_OVER;
        }
    } else {  // draw
        dl = alloc_display_list(16 * sizeof(*dl));
        dlIter = dl;
        if (sGameOverTableIndex == -2) {
            if (sGameOverFrameCounter == 180) {
                sGameOverTableIndex++;
                sGameOverFrameCounter = 0;
            }
        } else {
            // transition tile from "Game Over" to "Super Mario 64"
            if (sGameOverTableIndex != 11 && !(sGameOverFrameCounter & 0x1)) {
                // order of tiles that are flipped from "Game Over" to "Super Mario 64"
                static s8 flipOrder[] = { 0, 1, 2, 3, 7, 11, 10, 9, 8, 4, 5, 6 };

                sGameOverTableIndex++;
                gameOverBackgroundTable[flipOrder[sGameOverTableIndex]] =
                    INTRO_BACKGROUND_SUPER_MARIO;
            }
        }
        if (sGameOverTableIndex != 11) {
            sGameOverFrameCounter++;
        }
        graphNode->flags = (graphNode->flags & 0xFF) | (LAYER_OPAQUE << 8);

        // draw all the tiles
        gSPDisplayList(dlIter++, &dl_proj_mtx_fullscreen);
        gSPDisplayList(dlIter++, &title_screen_bg_dl_0A000100);
        for (j = 0; j < ARRAY_COUNT(gameOverBackgroundTable); j++) {
            gSPDisplayList(dlIter++, intro_backdrop_one_image(j, gameOverBackgroundTable));
        }
        gSPDisplayList(dlIter++, &title_screen_bg_dl_0A000190);
        gSPEndDisplayList(dlIter);
    }
    return dl;
}
