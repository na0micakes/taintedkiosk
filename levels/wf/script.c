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
#include "levels/wf/header.h"

// Unlike most levels, some of the level geometry objects in WF are defined as regular objects instead of terrain objects.
// Some of them are still terrain objects, however.
static const LevelScript script_func_local_1[] = {
    OBJECT(/*model*/ MODEL_LEVEL_GEOMETRY_03, /*pos*/  2305, 2432,  -255, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvStaticObject),
    OBJECT(/*model*/ MODEL_LEVEL_GEOMETRY_04, /*pos*/  3405, 1664, -1791, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvStaticObject),
    OBJECT(/*model*/ MODEL_LEVEL_GEOMETRY_05, /*pos*/  3840,    0, -2303, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvStaticObject),
    OBJECT(/*model*/ MODEL_LEVEL_GEOMETRY_05, /*pos*/  3840,    0, -1279, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvStaticObject),
    OBJECT(/*model*/ MODEL_LEVEL_GEOMETRY_06, /*pos*/     0,    0,     0, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvStaticObject),
    OBJECT(/*model*/ MODEL_LEVEL_GEOMETRY_07, /*pos*/  1757, 3519, -3151, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvStaticObject),
    OBJECT(/*model*/ MODEL_LEVEL_GEOMETRY_0A, /*pos*/  3840,  794,  2688, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvStaticObject),
    OBJECT(/*model*/ MODEL_LEVEL_GEOMETRY_0C, /*pos*/  1408, 2522,  2431, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvStaticObject),
    OBJECT(/*model*/ MODEL_WF_GIANT_POLE,     /*pos*/ -2560, 2560,  -256, /*angle*/ 0, 0, 0, /*bhvParam*/ 0, /*bhv*/ bhvGiantPole),
    RETURN(),
};

static const LevelScript script_func_local_2[] = {
    OBJECT          (/*model*/ MODEL_WF_SMALL_BOMP,               /*pos*/  3300, 1070,     1, /*angle*/ 0,  90, 0, /*bhvParam*/ 0, /*bhv*/ bhvSmallBomp),
    OBJECT          (/*model*/ MODEL_WF_SMALL_BOMP,               /*pos*/  3300, 1070,  1281, /*angle*/ 0,  90, 0, /*bhvParam*/ 0, /*bhv*/ bhvSmallBomp),
    OBJECT          (/*model*/ MODEL_WF_LARGE_BOMP,               /*pos*/  3300, 1070,   641, /*angle*/ 0,   0, 0, /*bhvParam*/ 0, /*bhv*/ bhvLargeBomp),
    OBJECT          (/*model*/ MODEL_WF_ROTATING_WOODEN_PLATFORM, /*pos*/  -255, 2560,  2304, /*angle*/ 0,   0, 0, /*bhvParam*/ 0, /*bhv*/ bhvWFRotatingWoodenPlatform),
    OBJECT          (/*model*/ MODEL_WF_SLIDING_PLATFORM,         /*pos*/  3328, 1075, -1791, /*angle*/ 0,  90, 0, /*bhvParam*/ BPARAM2(WF_SLID_BRICK_PTFM_BP_MOV_VEL_15), /*bhv*/ bhvWFSlidingPlatform),
    OBJECT          (/*model*/ MODEL_WF_SLIDING_PLATFORM,         /*pos*/  3328, 1075,  -767, /*angle*/ 0,  90, 0, /*bhvParam*/ BPARAM2(WF_SLID_BRICK_PTFM_BP_MOV_VEL_10), /*bhv*/ bhvWFSlidingPlatform),
    OBJECT          (/*model*/ MODEL_WF_SLIDING_PLATFORM,         /*pos*/  3328, 1075, -2815, /*angle*/ 0,  90, 0, /*bhvParam*/ BPARAM2(WF_SLID_BRICK_PTFM_BP_MOV_VEL_20), /*bhv*/ bhvWFSlidingPlatform),
    OBJECT          (/*model*/ MODEL_WF_TUMBLING_BRIDGE,          /*pos*/  1792, 2496,  1600, /*angle*/ 0,   0, 0, /*bhvParam*/ BPARAM2(TUMBLING_BRIDGE_BP_WF), /*bhv*/ bhvTumblingBridge),
    OBJECT          (/*model*/ MODEL_WF_BREAKABLE_WALL_RIGHT,     /*pos*/   512, 2176,  2944, /*angle*/ 0,   0, 0, /*bhvParam*/ 0, /*bhv*/ bhvWFBreakableWallRight),
    OBJECT          (/*model*/ MODEL_WF_BREAKABLE_WALL_LEFT,      /*pos*/ -1023, 2176,  2944, /*angle*/ 0,   0, 0, /*bhvParam*/ 0, /*bhv*/ bhvWFBreakableWallLeft),
    OBJECT_WITH_ACTS(/*model*/ MODEL_WF_KICKABLE_BOARD,           /*pos*/    13, 3584, -1407, /*angle*/ 0, 315, 0, /*bhvParam*/ 0, /*bhv*/ bhvKickableBoard, /*acts*/ ACT_2 | ACT_3 | ACT_4 | ACT_5 | ACT_6),
    OBJECT_WITH_ACTS(/*model*/ MODEL_1UP,                         /*pos*/  -384, 3584,     6, /*angle*/ 0,   0, 0, /*bhvParam*/ BPARAM2(ONE_UP_BP_GENERIC), /*bhv*/ bhv1Up,            /*acts*/ ACT_2 | ACT_3 | ACT_4 | ACT_5 | ACT_6),
    OBJECT          (/*model*/ MODEL_WF_ROTATING_PLATFORM,        /*pos*/  2304, 3584, -2303, /*angle*/ 0,   0, 0, /*bhvParam*/ BPARAM1(0x08) | BPARAM2(ROTATING_PLATFORM_BP_WF), /*bhv*/ bhvRotatingPlatform),
    OBJECT          (/*model*/ MODEL_WF_ROTATING_PLATFORM,        /*pos*/  3200, 3328, -1791, /*angle*/ 0,   0, 0, /*bhvParam*/ BPARAM1(0x08) | BPARAM2(ROTATING_PLATFORM_BP_WF), /*bhv*/ bhvRotatingPlatform),
    OBJECT          (/*model*/ MODEL_WF_ROTATING_PLATFORM,        /*pos*/  2688, 3584,  -895, /*angle*/ 0,   0, 0, /*bhvParam*/ BPARAM1(0x08) | BPARAM2(ROTATING_PLATFORM_BP_WF), /*bhv*/ bhvRotatingPlatform),
    OBJECT          (/*model*/ MODEL_NONE,                        /*pos*/ -2495, 1331,  -256, /*angle*/ 0,   0, 0, /*bhvParam*/ BPARAM2(61), /*bhv*/ bhvPoleGrabbing),
    RETURN(),
};

static const LevelScript script_func_local_3[] = {
    OBJECT          (/*model*/ MODEL_THWOMP,            /*pos*/  3462, 1939, -1545, /*angle*/ 0,  180, 0, /*bhvParam*/ BPARAM2(0), /*bhv*/ bhvThwomp2),
    OBJECT          (/*model*/ MODEL_THWOMP,            /*pos*/  3462, 1075, -3314, /*angle*/ 0,   90, 0, /*bhvParam*/ BPARAM2(0), /*bhv*/ bhvThwomp),
    OBJECT          (/*model*/ MODEL_NONE,              /*pos*/  -856,  922,  3819, /*angle*/ 0,    0, 0, /*bhvParam*/ 0, /*bhv*/ bhvBetaFishSplashSpawner),
    OBJECT          (/*model*/ MODEL_PIRANHA_PLANT,     /*pos*/  1822, 2560,  -101, /*angle*/ 0,   90, 0, /*bhvParam*/ 0, /*bhv*/ bhvPiranhaPlant),
    OBJECT          (/*model*/ MODEL_PIRANHA_PLANT,     /*pos*/  4625,  256,  5017, /*angle*/ 0,  -90, 0, /*bhvParam*/ 0, /*bhv*/ bhvPiranhaPlant),
    OBJECT          (/*model*/ MODEL_PIRANHA_PLANT,     /*pos*/   689, 2560,  1845, /*angle*/ 0,   90, 0, /*bhvParam*/ 0, /*bhv*/ bhvPiranhaPlant),
    OBJECT          (/*model*/ MODEL_WHOMP,             /*pos*/ -1545, 2560,  -286, /*angle*/ 0,    0, 0, /*bhvParam*/ BPARAM2(WHOMP_BP_SMALL), /*bhv*/ bhvSmallWhomp),
    OBJECT          (/*model*/ MODEL_WHOMP,             /*pos*/   189, 2560, -1857, /*angle*/ 0, -135, 0, /*bhvParam*/ BPARAM2(WHOMP_BP_SMALL), /*bhv*/ bhvSmallWhomp),
    OBJECT          (/*model*/ MODEL_BUTTERFLY,         /*pos*/  4736,  256,  4992, /*angle*/ 0,    0, 0, /*bhvParam*/ 0, /*bhv*/ bhvButterfly),
    OBJECT          (/*model*/ MODEL_BUTTERFLY,         /*pos*/  4608,  256,  5120, /*angle*/ 0,    0, 0, /*bhvParam*/ 0, /*bhv*/ bhvButterfly),
    OBJECT          (/*model*/ MODEL_BUTTERFLY,         /*pos*/  4608,  256,  4992, /*angle*/ 0,    0, 0, /*bhvParam*/ 0, /*bhv*/ bhvButterfly),
    OBJECT          (/*model*/ MODEL_BUTTERFLY,         /*pos*/  4608,  256,  4864, /*angle*/ 0,    0, 0, /*bhvParam*/ 0, /*bhv*/ bhvButterfly),
    OBJECT          (/*model*/ MODEL_BUTTERFLY,         /*pos*/  4480,  256,  4992, /*angle*/ 0,    0, 0, /*bhvParam*/ 0, /*bhv*/ bhvButterfly),
    OBJECT          (/*model*/ MODEL_BUTTERFLY,         /*pos*/  4608,  256,   256, /*angle*/ 0,    0, 0, /*bhvParam*/ 0, /*bhv*/ bhvButterfly),
    OBJECT          (/*model*/ MODEL_BUTTERFLY,         /*pos*/  4736,  256,   128, /*angle*/ 0,    0, 0, /*bhvParam*/ 0, /*bhv*/ bhvButterfly),
    OBJECT          (/*model*/ MODEL_BUTTERFLY,         /*pos*/  4480,  256,   128, /*angle*/ 0,    0, 0, /*bhvParam*/ 0, /*bhv*/ bhvButterfly),
    OBJECT          (/*model*/ MODEL_BUTTERFLY,         /*pos*/  4608,  256,     0, /*angle*/ 0,    0, 0, /*bhvParam*/ 0, /*bhv*/ bhvButterfly),
    OBJECT          (/*model*/ MODEL_BUTTERFLY,         /*pos*/  4608,  256,   128, /*angle*/ 0,    0, 0, /*bhvParam*/ 0, /*bhv*/ bhvButterfly),
    OBJECT          (/*model*/ MODEL_NONE,              /*pos*/  1035, 2880,  -900, /*angle*/ 0,   45, 0, /*bhvParam*/ BPARAM1(0) | BPARAM2(0), /*bhv*/ bhvCheckerboardElevatorGroup),
    OBJECT_WITH_ACTS(/*model*/ MODEL_BULLET_BILL,       /*pos*/  1280, 3712,   968, /*angle*/ 0,  180, 0, /*bhvParam*/ 0, /*bhv*/ bhvBulletBill,               /*acts*/ ALL_ACTS),
    OBJECT_WITH_ACTS(/*model*/ MODEL_LEVEL_GEOMETRY_08, /*pos*/     0, 3584,     0, /*angle*/ 0,    0, 0, /*bhvParam*/ 0, /*bhv*/ bhvTower,                     /*acts*/ ALL_ACTS),
    OBJECT_WITH_ACTS(/*model*/ MODEL_LEVEL_GEOMETRY_09, /*pos*/  1280, 3584,   896, /*angle*/ 0,    0, 0, /*bhvParam*/ 0, /*bhv*/ bhvBulletBillCannon,        /*acts*/ ALL_ACTS),
    OBJECT_WITH_ACTS(/*model*/ MODEL_NONE,              /*pos*/     0, 3483,     0, /*angle*/ 0,    0, 0, /*bhvParam*/ 0, /*bhv*/ bhvTowerPlatformGroup,      /*acts*/ ALL_ACTS),
    OBJECT_WITH_ACTS(/*model*/ MODEL_WF_TOWER_DOOR,     /*pos*/  -511, 3584,     0, /*angle*/ 0,    0, 0, /*bhvParam*/ 0, /*bhv*/ bhvTowerDoor,                /*acts*/ ALL_ACTS),
    OBJECT_WITH_ACTS(/*model*/ MODEL_BOBOMB_BUDDY,      /*pos*/ -1700, 1140,  3500, /*angle*/ 0,    0, 0, /*bhvParam*/ 0, /*bhv*/ bhvBobombBuddyOpensCannon, /*acts*/ ALL_ACTS),
    OBJECT_WITH_ACTS(/*model*/ MODEL_HOOT,              /*pos*/  2560,  700,  4608, /*angle*/ 0,    0, 0, /*bhvParam*/ 0, /*bhv*/ bhvHoot,                      /*acts*/ ALL_ACTS),
    RETURN(),
};

static const LevelScript script_func_local_4[] = {
    OBJECT_WITH_ACTS(/*model*/ MODEL_STAR,  /*pos*/   300, 5550,    0, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM1(STAR_INDEX_ACT_2), /*bhv*/ bhvStar,                 /*acts*/ ALL_ACTS),
    OBJECT_WITH_ACTS(/*model*/ MODEL_STAR,  /*pos*/ -2500, 1500, -750, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM1(STAR_INDEX_ACT_3), /*bhv*/ bhvStar,                 /*acts*/ ALL_ACTS),
    OBJECT_WITH_ACTS(/*model*/ MODEL_NONE,  /*pos*/  4600,  550, 2500, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM1(STAR_INDEX_ACT_4), /*bhv*/ bhvHiddenRedCoinStar, /*acts*/ ALL_ACTS),
    OBJECT_WITH_ACTS(/*model*/ MODEL_STAR,  /*pos*/  2880, 4300,  190, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM1(STAR_INDEX_ACT_5), /*bhv*/ bhvStar,                 /*acts*/ ALL_ACTS),
    OBJECT_WITH_ACTS(/*model*/ MODEL_STAR,  /*pos*/   590, 2450, 2650, /*angle*/ 0, 0, 0, /*bhvParam*/ BPARAM1(STAR_INDEX_ACT_6), /*bhv*/ bhvStar,                 /*acts*/ ALL_ACTS),
    RETURN(),
};

const LevelScript level_wf_entry[] = {
    INIT_LEVEL(),
    LOAD_MIO0        (/*seg*/ 0x07, _wf_segment_7SegmentRomStart, _wf_segment_7SegmentRomEnd),
    LOAD_MIO0        (/*seg*/ 0x0A, _cloud_floor_skybox_mio0SegmentRomStart, _cloud_floor_skybox_mio0SegmentRomEnd),
    LOAD_MIO0_TEXTURE(/*seg*/ 0x09, _grass_mio0SegmentRomStart, _grass_mio0SegmentRomEnd),
    LOAD_MIO0        (/*seg*/ 0x05, _group1_mio0SegmentRomStart, _group1_mio0SegmentRomEnd),
    LOAD_RAW         (/*seg*/ 0x0C, _group1_geoSegmentRomStart,  _group1_geoSegmentRomEnd),
    LOAD_MIO0        (/*seg*/ 0x06, _group14_mio0SegmentRomStart, _group14_mio0SegmentRomEnd),
    LOAD_RAW         (/*seg*/ 0x0D, _group14_geoSegmentRomStart,  _group14_geoSegmentRomEnd),
    LOAD_MIO0        (/*seg*/ 0x08, _common0_mio0SegmentRomStart, _common0_mio0SegmentRomEnd),
    LOAD_RAW         (/*seg*/ 0x0F, _common0_geoSegmentRomStart,  _common0_geoSegmentRomEnd),
    ALLOC_LEVEL_POOL(),
    MARIO(/*model*/ MODEL_MARIO, /*bhvParam*/ BPARAM4(0x01), /*bhv*/ bhvMario),
    JUMP_LINK(script_func_global_1),
    JUMP_LINK(script_func_global_2),
    JUMP_LINK(script_func_global_15),
    LOAD_MODEL_FROM_GEO(MODEL_WF_BUBBLY_TREE,                   bubbly_tree_geo),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_03,                wf_geo_0007E0),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_04,                wf_geo_000820),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_05,                wf_geo_000860),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_06,                wf_geo_000878),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_07,                wf_geo_000890),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_08,                wf_geo_0008A8),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_09,                wf_geo_0008E8),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0A,                wf_geo_000900),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0C,                wf_geo_000940),
    LOAD_MODEL_FROM_GEO(MODEL_WF_GIANT_POLE,                    wf_geo_000AE0),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0E,                wf_geo_000958),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0F,                wf_geo_0009A0),
    LOAD_MODEL_FROM_GEO(MODEL_WF_ROTATING_PLATFORM,             wf_geo_0009B8),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_11,                wf_geo_0009D0),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_12,                wf_geo_0009E8),
    LOAD_MODEL_FROM_GEO(MODEL_WF_SMALL_BOMP,                    wf_geo_000A00),
    LOAD_MODEL_FROM_GEO(MODEL_WF_LARGE_BOMP,                    wf_geo_000A40),
    LOAD_MODEL_FROM_GEO(MODEL_WF_ROTATING_WOODEN_PLATFORM,      wf_geo_000A58),
    LOAD_MODEL_FROM_GEO(MODEL_WF_SLIDING_PLATFORM,              wf_geo_000A98),
    LOAD_MODEL_FROM_GEO(MODEL_WF_TUMBLING_BRIDGE_PART,          wf_geo_000AB0),
    LOAD_MODEL_FROM_GEO(MODEL_WF_TUMBLING_BRIDGE,               wf_geo_000AC8),
    LOAD_MODEL_FROM_GEO(MODEL_WF_TOWER_TRAPEZOID_PLATORM,       wf_geo_000AF8),
    LOAD_MODEL_FROM_GEO(MODEL_WF_TOWER_SQUARE_PLATORM,          wf_geo_000B10),
    LOAD_MODEL_FROM_GEO(MODEL_WF_TOWER_SQUARE_PLATORM_UNUSED,   wf_geo_000B38),
    LOAD_MODEL_FROM_GEO(MODEL_WF_TOWER_SQUARE_PLATORM_ELEVATOR, wf_geo_000B60),
    LOAD_MODEL_FROM_GEO(MODEL_WF_BREAKABLE_WALL_RIGHT,          wf_geo_000B78),
    LOAD_MODEL_FROM_GEO(MODEL_WF_BREAKABLE_WALL_LEFT,           wf_geo_000B90),
    LOAD_MODEL_FROM_GEO(MODEL_WF_KICKABLE_BOARD,                wf_geo_000BA8),
    LOAD_MODEL_FROM_GEO(MODEL_WF_TOWER_DOOR,                    wf_geo_000BE0),
    LOAD_MODEL_FROM_GEO(MODEL_WF_KICKABLE_BOARD_FELLED,         wf_geo_000BC8),

    AREA(/*index*/ 1, wf_geo_000BF8),
        OBJECT(/*model*/ MODEL_NONE, /*pos*/  2600, 1256,  5120, /*angle*/ 0, 90, 0, /*bhvParam*/ BPARAM2(WARP_NODE_0A), /*bhv*/ bhvSpinAirborneWarp),
        OBJECT(/*model*/ MODEL_NONE, /*pos*/ -2925, 2560,  -947, /*angle*/ 0, 19, 0, /*bhvParam*/ BPARAM2(WARP_NODE_0B), /*bhv*/ bhvFadingWarp),
        OBJECT(/*model*/ MODEL_NONE, /*pos*/  2548, 1075, -3962, /*angle*/ 0, 51, 0, /*bhvParam*/ BPARAM2(WARP_NODE_0C), /*bhv*/ bhvFadingWarp),
        WARP_NODE(/*id*/ WARP_NODE_0A,      /*destLevel*/ LEVEL_WF,     /*destArea*/ 1, /*destNode*/ WARP_NODE_0A, /*flags*/ WARP_NO_CHECKPOINT),
        WARP_NODE(/*id*/ WARP_NODE_0B,      /*destLevel*/ LEVEL_WF,     /*destArea*/ 1, /*destNode*/ WARP_NODE_0C, /*flags*/ WARP_NO_CHECKPOINT),
        WARP_NODE(/*id*/ WARP_NODE_0C,      /*destLevel*/ LEVEL_WF,     /*destArea*/ 1, /*destNode*/ WARP_NODE_0B, /*flags*/ WARP_NO_CHECKPOINT),
        WARP_NODE(/*id*/ WARP_NODE_SUCCESS, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 1, /*destNode*/ WARP_NODE_34, /*flags*/ WARP_NO_CHECKPOINT),
        WARP_NODE(/*id*/ WARP_NODE_DEATH,   /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 1, /*destNode*/ WARP_NODE_66, /*flags*/ WARP_NO_CHECKPOINT),
        JUMP_LINK(script_func_local_1),
        JUMP_LINK(script_func_local_2),
        JUMP_LINK(script_func_local_3),
        JUMP_LINK(script_func_local_4),
        TERRAIN(/*terrainData*/ wf_seg7_collision_070102D8),
        MACRO_OBJECTS(/*objList*/ wf_seg7_macro_objs),
        SHOW_DIALOG(/*index*/ 0x00, DIALOG_030),
        SET_BACKGROUND_MUSIC(/*settingsPreset*/ 0x0005, /*seq*/ SEQ_LEVEL_GRASS),
        TERRAIN_TYPE(/*terrainType*/ TERRAIN_STONE),
    END_AREA(),

    FREE_LEVEL_POOL(),
    MARIO_POS(/*area*/ 1, /*yaw*/ 90, /*pos*/ 2600, 256, 5120),
    CALL(/*arg*/ 0, /*func*/ lvl_init_or_update),
    CALL_LOOP(/*arg*/ 1, /*func*/ lvl_init_or_update),
    CLEAR_LEVEL(),
    SLEEP_BEFORE_EXIT(/*frames*/ 1),
    EXIT(),
};
