#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "dialog_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/level_update.h"

#include "levels/scripts.h"

#include "actors/common1.h"

#include "make_const_nonconst.h"
#include "levels/vcutm/header.h"

static const LevelScript script_func_local_1[] = {
    OBJECT(/*model*/ MODEL_VCUTM_SEESAW_PLATFORM, /*pos*/   154, -1919, -6256, /*angle*/ 0, 270, 0, /*bhvParam*/ BPARAM2(0x07), /*bhv*/ bhvSeesawPlatform),
    OBJECT(/*model*/ MODEL_VCUTM_SEESAW_PLATFORM, /*pos*/ -2047, -3378, -2047, /*angle*/ 0,   0, 0, /*bhvParam*/ BPARAM2(0x07), /*bhv*/ bhvSeesawPlatform),
    //! @bug invalid model IDs - model ID 0x37 isn't loaded
    OBJECT(/*model*/ MODEL_VCUTM_CHECKERBOARD_PLATFORM_SPAWNER,           /*pos*/  3251, -1082, -6256, /*angle*/ 0, 270, 0, /*bhvParam*/ BPARAM1(1) | BPARAM2(75), /*bhv*/ bhvCheckerboardElevatorGroup),
    OBJECT(/*model*/ MODEL_VCUTM_CHECKERBOARD_PLATFORM_SPAWNER,           /*pos*/  2355, -1901, -6256, /*angle*/ 0, 270, 0, /*bhvParam*/ BPARAM1(1) | BPARAM2(75), /*bhv*/ bhvCheckerboardElevatorGroup),
    OBJECT(/*model*/ MODEL_VCUTM_CHECKERBOARD_PLATFORM_SPAWNER,           /*pos*/  1459, -1594, -6256, /*angle*/ 0,  90, 0, /*bhvParam*/ BPARAM1(1) | BPARAM2(75), /*bhv*/ bhvCheckerboardElevatorGroup),
    OBJECT(/*model*/ MODEL_VCUTM_CHECKERBOARD_PLATFORM_SPAWNER,           /*pos*/ -1151, -2413, -6256, /*angle*/ 0, 270, 0, /*bhvParam*/ BPARAM1(1) | BPARAM2(75), /*bhv*/ bhvCheckerboardElevatorGroup),
    RETURN(),
};

static const LevelScript script_func_local_3[] = {
    OBJECT(/*model*/ MODEL_NONE,       /*pos*/ 4600, 250, -4500, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM1(STAR_INDEX_ACT_1), /*bhv*/ bhvHiddenRedCoinStar),
    RETURN(),
};

const LevelScript level_vcutm_entry[] = {
    INIT_LEVEL(),
    LOAD_MIO0_TEXTURE(/*seg*/ 0x09, _outside_mio0SegmentRomStart, _outside_mio0SegmentRomEnd),
    LOAD_MIO0        (/*seg*/ 0x07, _vcutm_segment_7SegmentRomStart, _vcutm_segment_7SegmentRomEnd),
    LOAD_MIO0        (/*seg*/ 0x05, _group8_mio0SegmentRomStart, _group8_mio0SegmentRomEnd),
    LOAD_RAW         (/*seg*/ 0x0C, _group8_geoSegmentRomStart,  _group8_geoSegmentRomEnd),
    LOAD_MIO0        (/*seg*/ 0x08, _common0_mio0SegmentRomStart, _common0_mio0SegmentRomEnd),
    LOAD_RAW         (/*seg*/ 0x0F, _common0_geoSegmentRomStart,  _common0_geoSegmentRomEnd),
    ALLOC_LEVEL_POOL(),
    MARIO(/*model*/ MODEL_MARIO, /*bhvParam*/ BPARAM4(0x01), /*bhv*/ bhvMario),
    JUMP_LINK(script_func_global_1),
    LOAD_MODEL_FROM_GEO(MODEL_VCUTM_SEESAW_PLATFORM, vcutm_geo_0001F0),
    LOAD_MODEL_FROM_GEO(MODEL_VCUTM_WARP_PIPE,       warp_pipe_geo),

    AREA(/*index*/ 1, vcutm_geo_000208),
        OBJECT(/*model*/ MODEL_NONE, /*pos*/ -6143, 6734, -6143, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM2(WARP_NODE_0A), /*bhv*/ bhvAirborneWarp),
        WARP_NODE(/*id*/ WARP_NODE_0A,         /*destLevel*/ LEVEL_VCUTM,          /*destArea*/ 1, /*destNode*/ WARP_NODE_0A, /*flags*/ WARP_NO_CHECKPOINT),
        WARP_NODE(/*id*/ WARP_NODE_WARP_FLOOR, /*destLevel*/ LEVEL_CASTLE_GROUNDS, /*destArea*/ 1, /*destNode*/ WARP_NODE_07, /*flags*/ WARP_NO_CHECKPOINT),
        WARP_NODE(/*id*/ WARP_NODE_SUCCESS,    /*destLevel*/ LEVEL_CASTLE_GROUNDS, /*destArea*/ 1, /*destNode*/ WARP_NODE_08, /*flags*/ WARP_NO_CHECKPOINT),
        WARP_NODE(/*id*/ WARP_NODE_DEATH,      /*destLevel*/ LEVEL_CASTLE_GROUNDS, /*destArea*/ 1, /*destNode*/ WARP_NODE_06, /*flags*/ WARP_NO_CHECKPOINT),
        JUMP_LINK(script_func_local_3),
        JUMP_LINK(script_func_local_1),
        TERRAIN(/*terrainData*/ vcutm_seg7_collision),
        MACRO_OBJECTS(/*objList*/ vcutm_seg7_macro_objs),
        SHOW_DIALOG(/*index*/ 0x00, DIALOG_129),
        SET_BACKGROUND_MUSIC(/*settingsPreset*/ 0x0000, /*seq*/ SEQ_LEVEL_SLIDE),
        TERRAIN_TYPE(/*terrainType*/ TERRAIN_STONE),
    END_AREA(),

    FREE_LEVEL_POOL(),
    MARIO_POS(/*area*/ 1, /*yaw*/ 0, /*pos*/ -6143, 5734, -6143),
    CALL(/*arg*/ 0, /*func*/ lvl_init_or_update),
    CALL_LOOP(/*arg*/ 1, /*func*/ lvl_init_or_update),
    CLEAR_LEVEL(),
    SLEEP_BEFORE_EXIT(/*frames*/ 1),
    EXIT(),
};
