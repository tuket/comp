struct HashMap (TK:type, TV:type) {
    
}

struct Allocator {
    alloc: func(n:usize) -> *u8;
    free: func(*u8);
}

func checkAllocatorSignature(allocator:$Allocator) -> bool
{
    if(@hasMember(Allocator, alloc) &&
       Allocator.@hasMember(alloc))
    {
        if(@getMember(Allocator, alloc).type  == func(usize)->*u8 && 
           Allocator.@getMember(free).type == func(*u8))
        {
            return true;
        }
    }
   return false;
}

func HashMap(TK:type, TV:type, allocator?:$Allocator) -> type
{
    return struct {
        struct Entry { key:TK; val:TV; }
        const allocator := #provided(allocator) ? allocator : defaultAllocator;
        entries:Entry[],
    }
}

func init(m:HashMap($TK:type, $TV:type))
{
    const HM = HashMap($TK:type, $TV:type);
    const NUM_INIT_ELEMS := 16;
    m.entries = m.allocator.alloc(NUM_INIT_ELEMS * @size(HM.Entry))[:NUM_INIT_ELEMS]; // maybe it should be .@allocator or .s_allocator
}

func deinit(m_HashMap($TK:type, $TV:type))
{
    m.allocator.free(m.emtries);
}

func add(m:HashMap($TK:type, $TV:type), key:TK, val:TV)
    -> *HashMap(TK:type, TV:type).Entry
{

}

func remove(m:HashMap($TK:type, $TV:type)), key:TK) -> wasRemoved:bool
{
    m.entries
}