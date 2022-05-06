

实现一段代码，每个动物都自我介绍了一遍。我们的目标是，只让<code>Cat</code>做出自我介绍，但是不使用<code>dynamic_cast</code>（或者针对<code>shared_ptr</code>也有<code>dynamic_pointer_cast</code>，区别在于尖括号内只需要类名，不需要指针类型）来判断。</p>

<p>采用<code>dynamic_cast</code>相比 visitor 模式有以下弊端。</p>

- 存在多个派生类需要做不同的事情的时候，多个<code>if</code>和<code>dynamic_cast</code>会导致性能低下，代码结构也会变得混乱。
- 每次添加一个新的子类，都需要找到所有需要添加新分支的<code>if</code>。
- 添加关于所有类的一个新逻辑的时候，又需要针对所有类写一个<code>if</code>,不仅容易混乱，而且不利于编译器查漏补缺。

采用visitor有以下好处。
<ul><li>因为这毕竟是一个O(1)跳转，不同的类只需要跳转一次就可以运行相应的函数（而不是用<code>if</code>一个一个尝试），性能高。</li><li>当你添加一个新的子类的时候，只要你 visitor 接口的成员都是纯虚类，你很容易通过阅读所有编译错误来找出所有需要修改。</li><li>添加关于所有的类的一个新的逻辑很容易，就是继承自接口，井井有条。</li></ul>
