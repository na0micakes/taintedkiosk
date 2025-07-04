// switch_hidden_objects.inc.c

struct ObjectHitbox sBreakableBoxHitbox = {
    /* interactType:      */ INTERACT_BREAKABLE,
    /* downOffset:        */ 20,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 1,
    /* numLootCoins:      */ 0,
    /* radius:            */ 150,
    /* height:            */ 200,
    /* hurtboxRadius:     */ 150,
    /* hurtboxHeight:     */ 200,
};

void breakable_box_init(void) {
    o->oHiddenObjectPurpleSwitch = NULL;
    o->oAnimState = 1;

    switch (o->oBhvParams2ndByte) {
        case BREAKABLE_BOX_BP_NO_COINS:
            o->oNumLootCoins = 0;
            break;
        case BREAKABLE_BOX_BP_3_COINS:
            o->oNumLootCoins = 3;
            break;
        case BREAKABLE_BOX_BP_5_COINS:
            o->oNumLootCoins = 5;
            break;
        case BREAKABLE_BOX_BP_GIANT:
            cur_obj_scale(1.5f);
            break;
    }
}

void hidden_breakable_box_actions(void) {
    struct Object *purpleSwitch;

    obj_set_hitbox(o, &sBreakableBoxHitbox);
    cur_obj_set_model(MODEL_BREAKABLE_BOX_SMALL);

    if (o->oAction == HIDDEN_OBJECT_ACT_INACTIVE) {
        cur_obj_disable_rendering();
        cur_obj_become_intangible();
        if (o->oTimer == 0) {
            breakable_box_init();
        }
    } else if (o->oAction == HIDDEN_OBJECT_ACT_ACTIVE) {
        cur_obj_become_tangible();
        if (cur_obj_wait_then_blink(360, 20)) {
            o->oAction = HIDDEN_OBJECT_ACT_INACTIVE;
        }
        if (cur_obj_was_attacked_or_ground_pounded()) {
            spawn_mist_particles();
            spawn_triangle_break_particles(30, MODEL_DIRT_ANIMATION, 3.0f, 4);
            o->oAction++;
            cur_obj_play_sound_2(SOUND_GENERAL_BREAK_BOX);
        }
        load_object_collision_model();
    } else { // HIDDEN_OBJECT_ACT_BROKEN
        cur_obj_become_intangible();
        cur_obj_disable_rendering();
        o->oInteractStatus = 0;
    }
}

void hidden_wdw_platform_actions(void) {
    struct Object *purpleSwitch;

    obj_set_collision_data(o, wdw_seg7_collision_07018528);

    if (o->oAction == HIDDEN_OBJECT_ACT_INACTIVE) {
        cur_obj_disable_rendering();
        cur_obj_become_intangible();
    } else { // HIDDEN_OBJECT_ACT_ACTIVE
        cur_obj_become_tangible();
        if (cur_obj_wait_then_blink(360, 20)) {
            o->oAction = HIDDEN_OBJECT_ACT_INACTIVE;
        }
        load_object_collision_model();
    }
}

void bhv_hidden_object_loop(void) {
    if (o->oBhvParams2ndByte == HIDDEN_OBJECT_BP_BREAKABLE_BOX) {
        hidden_breakable_box_actions();
    } else {
        hidden_wdw_platform_actions();
    }
}
