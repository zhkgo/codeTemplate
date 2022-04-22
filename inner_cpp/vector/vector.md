### 基于move和placement new实现简易vector

实现右值引用构造函数、析构函数及以下函数。
- void Add(const T& item)这个函数类似于std::vector提供的push_back方法，作用是向当前元素数组的末尾添加一个新的元素——如果内存空间不足的话你就需要对内存进行重新分配，不能让Vector类的使用者自己去考虑数组是否会越界的问题。
- bool Insert(const T& item,int index)向索引index的位置插入元素——然后将index后面的元素依次向后移动一个位置。同样，你需要自己处理内存空间问题。除此之外，你还要检查索引是否合法——如果合法则返回true，不合法则直接返回false，不执行任何操作。
- bool Remove(int index)删除索引index位置的元素，并且将index后面的所有元素向前移动一位。其他细节跟Insert函数保持一致。
- int Contains(const T& item)遍历整个数组，看是否包含元素item。如果包含则返回item的索引，如果不包含则返回-1
- void Clear()清除Vector的所有元素，将指针置为nullptr，将计数器归零——注意为了避免内存泄漏，Clear()和Vector的析构函数必须要先调用所有元素的析构函数再对堆内存进行free

测试输出
```
ctor
copy ctor
dtor
ctor
right value ctor
copy ctor
dtor
dtor
ctor
right value ctor
right value ctor
copy ctor
dtor
dtor
dtor
ctor
right value ctor
right value ctor
right value ctor
copy ctor
dtor
dtor
dtor
dtor
0 1 2 3 
ctor
right value ctor
right value ctor
copy ctor
right value ctor
right value ctor
dtor
dtor
dtor
dtor
0 1 4 2 3 
right value ctor
right value ctor
right value ctor
right value ctor
dtor
dtor
dtor
dtor
dtor
0 1 2 3 
ctor
ctor
1
-1
0 1 2 3 
copy ctor
1 
dtor
dtor
dtor
dtor
dtor
dtor
dtor
dtor
dtor
dtor
dtor
dtor 
```