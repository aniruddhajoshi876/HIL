// Copyright 2006-2026 Speedgoat GmbH

#ifndef z82ee9baa10
#define z82ee9baa10
#ifdef __cplusplus
extern"C"{
#endif
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
typedef struct zb9965076ff{uint32_t type;uint32_t id;uint64_t uid;void*custom_data;}sg_block_info;typedef struct z262af189b3 z0486a44979;typedef struct z4f603a54fb{uint32_t type;uint32_t id;bool is_initiator;int32_t pci_bus;int32_t pci_slot;void*custom_data;z0486a44979*z0a9c26677d;}sg_mod_info;typedef struct z35955cb02c{sg_block_info**zc94806dc09;uint32_t Length;uint32_t zab038c343f;}z435e1f7ee2;typedef struct z262af189b3{z435e1f7ee2**types;uint32_t Length;uint32_t zdd54ef64f0;uint32_t zab038c343f;}z0486a44979;typedef struct zfbb075eb64{sg_mod_info**z93394b1cef;uint32_t Length;uint32_t z2219417de1;}zfdad121cb9;typedef struct z4031f7db4f{zfdad121cb9**types;uint32_t Length;uint32_t z4e150cf6a9;uint32_t z2219417de1;}z26c2f76b9c;extern z26c2f76b9c*zdb448ba0d8;typedef sg_mod_info**sg_mod_list;sg_mod_info*sg_module_register(uint32_t zbc7e7e4c6d,uint32_t zc6f60ee1c8);void sg_module_unregister(uint32_t zbc7e7e4c6d,uint32_t zc6f60ee1c8);int32_t sg_module_get(sg_mod_list*z93394b1cef,uint32_t zbc7e7e4c6d,int32_t zc6f60ee1c8);sg_mod_info*sg_module_get_single(uint32_t zbc7e7e4c6d,uint32_t zc6f60ee1c8);void*sg_module_get_custom_data(uint32_t zbc7e7e4c6d,uint32_t zc6f60ee1c8);void*sg_module_alloc_custom_data(sg_mod_info*module,uint32_t nBytes);sg_block_info*sg_block_register(sg_mod_info*module,uint32_t z20660c3e9c,uint32_t z1383b49cab);void sg_block_unregister(sg_mod_info*module,uint32_t z20660c3e9c,uint32_t z1383b49cab);sg_block_info*sg_block_get(sg_mod_info*module,uint32_t z20660c3e9c,uint32_t z1383b49cab);sg_block_info*sg_block_register_with_uid(sg_mod_info*module,uint32_t z20660c3e9c,uint64_t uid);sg_block_info*sg_block_get_by_uid(sg_mod_info*module,uint32_t z20660c3e9c,uint64_t uid);
#ifdef __cplusplus
}
#endif
#endif 

