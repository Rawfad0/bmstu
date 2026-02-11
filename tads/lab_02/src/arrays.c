#include "arrays.h"

size_t paddings[TABLE_FIELDS+1] = {PADDING_4, LAST_NAME_LEN, FIRST_NAME_LEN, \
    GROUP_LEN, CHAR_LEN, AGE_LEN, GPA_LEN, DATE_LEN, ADDRESS_TYPE_LEN, \
    STREET_NAME_LEN, PADDING_10, PADDING_9, CHAR6};

char blanks_13[TABLE_FIELDS+1][MAX_FIELD_LEN] = {BLANKSx25, BLANKSx25, BLANKSx25, BLANKSx25, BLANKSx25, 
    BLANKSx25, BLANKSx25, BLANKSx25, BLANKSx25, BLANKSx25, BLANKSx25, BLANKSx25, BLANKSx25};

char table_fields[TABLE_FIELDS+1][MAX_FIELD_LEN] = {"N", "last_name", "first_name", "group", \
    "g", "age", "gpa", "date", "address_type", "street", "house/dorm", "flat/room", "cost"};


size_t key_table_paddings[KEY_TABLE_FIELDS+1] = {PADDING_4, LAST_NAME_LEN, PADDING_5};

char blanks_3[KEY_TABLE_FIELDS+1][MAX_FIELD_LEN] = {BLANKSx25, BLANKSx25, BLANKSx25};

char key_table_fields[KEY_TABLE_FIELDS+1][MAX_FIELD_LEN] = {"N", "last_name", "index"};


size_t field_sizes[TABLE_FIELDS - ADDRESS_FIELDS + 1] = {LAST_NAME_LEN, \
    FIRST_NAME_LEN, GROUP_LEN, GENDER_LEN, AGE_LEN, GPA_LEN, DATE_LEN, ADDRESS_TYPE_LEN};

size_t field_sizes_address_types[ADDRESS_TYPES][ADDRESS_FIELDS - 1] = {
    {STREET_NAME_LEN, CHAR3, CHAR4},
    {CHAR3, CHAR4},
    {STREET_NAME_LEN, CHAR3, CHAR4, CHAR6}};


char field_names[TABLE_FIELDS - ADDRESS_FIELDS + 1][MAX_FIELD_LEN] = {"last name", \
    "first name", "group", "gender", "age", "gpa", "enrollment date", "address type"};

char fields_names_address_types[ADDRESS_TYPES][ADDRESS_FIELDS - 1][MAX_FIELD_LEN] = {
    {"street", "house num", "flat num"},
    {"dorm num", "room num"},
    {"street", "house num", "flat num", "cost"}};


char masks[TABLE_FIELDS - ADDRESS_FIELDS + 1][MAX_MASK_LEN] = {
    MASK_LAST_NAME, MASK_FIRST_NAME, MASK_GROUP, MASK_GENDER, 
    MASK_AGE, MASK_GPA, MASK_DATE, MASK_ADDRESS_TYPE};

char masks_address_types[ADDRESS_TYPES][ADDRESS_FIELDS-1][MAX_MASK_LEN] = {
    {MASK_STREET, MASK_1to3_DIGITS, MASK_1to4_DIGITS},
    {MASK_1to3_DIGITS, MASK_1to4_DIGITS},
    {MASK_STREET, MASK_1to3_DIGITS, MASK_1to4_DIGITS, MASK_1to6_DIGITS}};

char masks_address_types_with_blanks[ADDRESS_TYPES][ADDRESS_FIELDS-1][MAX_MASK_LEN] = {
        {MASK_STREET, MASK_1to3_DIGITS, MASK_1to4_DIGITS, MASK_BLANK},
        {MASK_BLANK, MASK_1to3_DIGITS, MASK_1to4_DIGITS, MASK_BLANK},
        {MASK_STREET, MASK_1to3_DIGITS, MASK_1to4_DIGITS, MASK_1to6_DIGITS}};


char addresses[ADDRESS_TYPES][ADDRESS_TYPE_LEN] = {
    ADDRESS_TYPE_HOUSE, ADDRESS_TYPE_DORMITORY, ADDRESS_TYPE_RENTAL_PLACE};

size_t address_types_fields[ADDRESS_TYPES] = {ADDRESS_TYPE_HOUSE_FIELDS, 
    ADDRESS_TYPE_DORMITORY_FIELDS, ADDRESS_TYPE_RENTAL_PLACE_FIELDS};
