#pragma once



#define ELONA_SERIALIZATION_STRUCT_BEGIN(ar, struct_name) \
    auto&& ar_struct = ar.struct_begin(struct_name)

#define ELONA_SERIALIZATION_STRUCT_FIELD(value, field) \
    ELONA_SERIALIZATION_STRUCT_FIELD_WITH_NAME(value, #field, field)

#define ELONA_SERIALIZATION_STRUCT_FIELD_WITH_NAME(value, name, field) \
    ar_struct.struct_field(name, (value).field)

#define ELONA_SERIALIZATION_STRUCT_END() ar_struct.struct_end()
