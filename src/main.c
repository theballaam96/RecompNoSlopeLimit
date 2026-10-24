#include "modding.h"
#include "ultra64.h"
#include "recompconfig.h"
#include "recompdata.h"
#include "recompui.h"
#include "recompui_event_structs.h"
#include "rt64_extended_gbi.h"
#include "enums.h"
#include "common_structs.h"

typedef struct {
    s16 unk0;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    u8 unk8;
    u8 unk9;
} Struct80748D40;

extern Struct80748D40 D_global_asm_80748D40[19];
Struct80748D40 stored_values[19];
u8 is_stored = FALSE;
u8 applies_everywhere = FALSE;
u8 did_apply_everywhere = FALSE;

RECOMP_CALLBACK("*", dk64recomp_every_frame)
void removeSlopeLimit(void)
{
    s32 i;

    applies_everywhere = recomp_get_config_u32("applies_to_all") != 0;
    if (!is_stored) {
        for (i = 0; i < 19; i++) {
            stored_values[i] = D_global_asm_80748D40[i];
        }
        is_stored = TRUE;
    }
    if (applies_everywhere != did_apply_everywhere) {
        for (i = 0; i < 19; i++) {
            D_global_asm_80748D40[i].unk2 = stored_values[i].unk2;
            D_global_asm_80748D40[i].unk3 = stored_values[i].unk3;
        }
    }
    if (applies_everywhere) {
        for (i = 0; i < 19; i++) {
            D_global_asm_80748D40[i].unk2 = 0;
            D_global_asm_80748D40[i].unk3 = 0;
        }
    } else {
        D_global_asm_80748D40[16].unk2 = 0;
        D_global_asm_80748D40[16].unk3 = 0;
    }
    did_apply_everywhere = applies_everywhere;
}