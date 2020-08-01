func f(x int, y int) : int
{
    return x + y;
}

P := struct {
    x int;
    y int;
}

func +(a P, b P) : P
{
    return {
        .x = a.x + b.x,
        .y = a.y + b.y
    }
}

func Array(T type, ST ?type)
{
    return struct {
        _ptr *T,
        _size (type ? type : u32)
    };
}

func print(T type, T x)
{
    if T == i32 {

    }
    else if #is_struct(T) {
        for field : #fields(T) {
            print(x.#field);
        }
    }
}

FileHandle := struct {
    _sysPtr *u32;
}

func read(fh *FileHandle, T type, buf []T) {
    // read from the file to fub
}

func close(fh* FileHandle) {
    if #debug()
}

func sumArrays(T type, n u32, b [n]T, b [n]T) -> out [n]T
{
    for i := 0; i < n; i++ {
        out[i] = a[i] + b[i]
    }
}

func rand(T type) -> out T
{
    if T == i32 {
        out = randInt();
    }
    else {
        unreachable;
    }
}

func useSumArrays()
{
    n :u32 = 16;
    var a : [n]i32 = ---;
    var b : [n]i32 = ---;
    for i := 0; i < n; i++ {
        a[i] = rand(i32);
        b[i] = rand();
    }
    
    c : [n]i32 = sumArrays(n, a, b);
    c := sumArrays(n, a, b);
    c := sumArrays(a, b);
    sumArrays(a, b) -> c;
}

func createMesh(n u32, positions [n]Vec3, texCoords[n]Vec2) -> (u32 vao, u32 vbo)
{
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    //...
}

func useCreateMesh()
{
    (vao, vbo) := createMesh(...);
    (var vao, vbo) := createMesh(...);
    var (vao, vbo) := createMesh(...);
    createMesh(...) -> (vao, vbo);
    (vao : i32, vbo) := (i32, i32)createMesh(...);
}

func processFile(fileName CStr)
{
    file := fopen("file.txt", "rw");
    defer file.close()
    buf := malloc(u8, file.length()+1); // type is u8[file.length()+1]
    file.read(buf, file.length())
    buf[file.length()] = 0;
    for i := 0; i < len(buf); i++ {
        if buf[i] >= 'a' && buf[i] <= 'z' {
            buf[i] -= 'a';
            buf[i] += 'A';
        }
    }
    file.write(buf[:len(buf)-1]);
}

struct HashMap (KT type, VT type, alloc: func(uint)->*u8)
{
    struct Entry {
        key KT;
        val KV;
    }
    entries []Entry = null;
}

func [](m &HashMap(KT, VT), key KT) &VT
{
    for entry : m.entries {
        if entry.key == key {
            return entry.val;
        }
    }
}

const fn := func (a i8, b i8) -> i8; // this is a type alias
const fn := func (a i8, b i8) -> i8 { return a + b; } // this is a function pointer

func genFn(x $T) -> T { return x*x; }
const fn := genFn; // alias function
const fn_i32 := genFn(T:i32); // function ptr

func genFn(x:$TX, y:$TY) -> $TX { return x+TX(y); }
const fn := genFn(TX:i32); // partial specialization of types
const fn_i32_u32 _= genFn(TX:i32, TY:u32);

func add(m &HashMap(KT, VT), key KT, val VT) -> &HashMap(KT, VT)
{
    m.entries[]
}

func testHashMap() {
    m := HashMap(i32, f32){}
}

x : &int = 