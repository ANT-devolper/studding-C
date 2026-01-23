#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

/**
 * Definition of the types will use on arena_allocator
 */
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef i8 b8;
typedef i32 b32;

/**
 * Convert human values on bytes
 */
#define KiB(n) ((u64)(n) << 10)
#define MiB(n) ((u64)(n) << 20)
#define GiB(n) ((u64)(n) << 30)

/**
 * Comparation min and max macros
 */
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

/**
 * Aling macros
 */
#define ALING_UP_POW2(n, p) (((u64)(n) + ((u64)(p) - 1 )) & (~((u64)(p) - 1)))
#define ARENA_BASE_POS (sizeof(mem_arena))
#define ARENA_ALING (sizeof(void*))

typedef struct {
    u64 reserve_size;
    u64 commit_size;

    u64 pos;
    u64 commit_pos;
} mem_arena;

mem_arena* arena_create(u64 reserve_size, u64 commit_size);

void arena_destroy(mem_arena* arena);
void* arena_push(mem_arena* arena, u64 size, b32 non_zero);
void arena_pop(mem_arena* arena, u64 size);
void arena_pop_to(mem_arena* arena, u64 pos);
void arena_clear(mem_arena* arena);

#define PUSH_STRUCT(arena, T) (T*)arena_push((arena), sizeof(T), false)
#define PUSH_STRUCT_NZ(arena, T) (T*)arena_push((arena), sizeof(T), true)
#define PUSH_ARRAY(arena, T, n) (T*)arena_push((arena), sizeof(T) * (n), false)
#define PUSH_ARRAY_NZ(arena, T) (T*)arena_push((arena), sizeof(T) * (n), true)

void* plat_mem_reserve(u64 size);
b32 plat_mem_commit(void* ptr, u64 size);
b32 plat_mem_decommit(void* ptr, u64 size);
b32 plat_mem_release(void* ptr, u64 size);

int main(void){
    mem_arena* perm_arena = arena_create(GiB(1), MiB(1));

    while(1){
        arena_push(perm_arena, MiB(16), false);
        getc(stdin);
    }

    arena_destroy(perm_arena);
    
    return 0;
}

mem_arena* arena_create(u64 reserve_size, u64 commit_size){
    u32 pagesize = plat_get_pagesize();
    reserve_size = ALING_UP_POW2(reserve_size, pagesize);
    commit_size = ALING_UP_POW2(commit_size, pagesize);

    mem_arena* arena = plat_mem_reserve(reserve_size);

    if(!plat_mem_commit(arena, commit_size)){
        return NULL;
    }

    arena->reserve_size = reserve_size;
    arena->commit_size = commit_size;
    arena->pos = ARENA_BASE_POS;
    arena->commit_pos = commit_size;

    return arena;
}
void arena_destroy(mem_arena* arena){
    plat_mem__release(arena, arena->reserve_size);
}
void* arena_push(mem_arena* arena, u64 size, b32 non_zero){
    u64 pos_aligned = ALING_UP_POW2(arena->pos, ARENA_ALING);
    u64 new_pos = pos_aligned + size;

    if (new_pos > arena->reserve_size) return NULL;

    if (new_pos > arena->commit_pos){
        u64 new_commit_pos = new_pos;
        new_commit_pos += arena->commit_size - 1;
        new_commit_pos -= new_commit_pos % arena->commit_size;
        new_commit_pos = MIN(new_commit_pos, arena->reserve_size);
        
        u8* mem = (u8*)arena + arena->commit_pos;
        u64 commit_size = new_commit_pos - arena->commit_pos;

        if (!plat_mem_commit(mem, commit_size)) {
            return NULL;
        }

        arena->pos = new_pos;
    }
    
    arena->pos = new_pos;

    u8* out = (u8*)arena + pos_aligned;

    if (!non_zero) memset (out, 0, size);

    return out;
}
void arena_pop(mem_arena* arena, u64 size){
    size = MIN(size, arena->pos - ARENA_BASE_POS);
    arena->pos -= size;
}
void arena_pop_to(mem_arena* arena, u64 pos){
    u64 size = pos <arena->pos ? arena->pos - pos : 0;
    arena_pop(arena,size);
}
void arena_clear(mem_arena* arena){
    arena_pop_to(arena, ARENA_BASE_POS);
}

#ifdef _WIN32

    #include <windows.h>

    void* plat_mem_reserve(u64 size){
        SYSTEM_INFO sysinfo = { 0 };
        GetSystemInfo(&sysinfo);

        return sysinfo.dwPagesize;
    }
    b32 plat_mem_commit(void* ptr, u64 size){
        return VirtualAlloc(NULL, size, MEM_RESERVE, PAGE_READWRITE);
    }
    b32 plat_mem_decommit(void* ptr, u64 size){
        void* ret = VirtualAlloc(ptr, size, MEM_COMMIT, PAGE_READWRITE);
        return VirtualFree(ptr, size, MEM_DECOMMIT);
    }
    b32 plat_mem_release(void* ptr, u64 size){
        return VirtualFree(ptr, size, MEM_RELEASE);
    }

#endif