/* THIS FILE IS GENERATED, DO NOT EDIT! */

const firmware_crc_block_t firmware_100a_crc32[]={
    { (const char *)0xffc00000,   0x323f20, 0xf3e56fbf }, // ROMCODE, RAM data
};

firmware_crc_sub_t firmware_crc_list[]={
    { "GM1.00A", firmware_100a_crc32 },
};

const firmware_crc_desc_t firmware_crc_desc={
    (const char *)0xffc08055, // firmware_ver_ptr
    firmware_crc_list,
    1,  // sub_count
    1,  // block_count
};
