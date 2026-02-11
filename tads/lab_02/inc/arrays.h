#ifndef __ARRAYS__H__
#define __ARRAYS__H__

#include "consts.h"
#include "structs.h"

extern size_t paddings[TABLE_FIELDS+1];
extern char blanks_13[TABLE_FIELDS+1][MAX_FIELD_LEN];
extern char table_fields[TABLE_FIELDS+1][MAX_FIELD_LEN];

extern size_t key_table_paddings[KEY_TABLE_FIELDS+1];
extern char blanks_3[KEY_TABLE_FIELDS+1][MAX_FIELD_LEN];
extern char key_table_fields[KEY_TABLE_FIELDS+1][MAX_FIELD_LEN];

extern size_t field_sizes[TABLE_FIELDS - ADDRESS_FIELDS + 1];
extern size_t field_sizes_address_types[ADDRESS_TYPES][ADDRESS_FIELDS - 1];

extern char field_names[TABLE_FIELDS - ADDRESS_FIELDS + 1][MAX_FIELD_LEN];
extern char fields_names_address_types[ADDRESS_TYPES][ADDRESS_FIELDS - 1][MAX_FIELD_LEN];

extern char masks[TABLE_FIELDS - ADDRESS_FIELDS + 1][MAX_MASK_LEN];
extern char masks_address_types[ADDRESS_TYPES][ADDRESS_FIELDS-1][MAX_MASK_LEN];
extern char masks_address_types_with_blanks[ADDRESS_TYPES][ADDRESS_FIELDS-1][MAX_MASK_LEN];

extern char addresses[ADDRESS_TYPES][ADDRESS_TYPE_LEN];
extern size_t address_types_fields[ADDRESS_TYPES];

#endif