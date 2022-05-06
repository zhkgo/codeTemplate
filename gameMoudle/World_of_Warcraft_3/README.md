<dl class="problem-content">
		<dt>描述</dt>
		<dd><p class="MsoNormal" style="">魔兽世界的西面是红魔军的司令部，东面是蓝魔军的司令部。两个司令部之间是依次排列的若干城市，城市从西向东依次编号为<span>1,2,3 .... N ( N &lt;= 20)</span>。红魔军的司令部算作编号为<span>0</span>的城市，蓝魔军的司令部算作编号为<span>N+1</span>的城市。司令部有生命元，用于制造武士。</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="">两军的司令部都会制造武士。武士一共有<span>dragon </span>、<span>ninja</span>、<span>iceman</span>、<span>lion</span>、<span>wolf </span>五种。每种武士都有编号、生命值、攻击力这三种属性。</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="">双方的武士编号都是从<span>1</span>开始计算。红方制造出来的第<span>n </span>个武士，编号就是<span>n</span>。同样，蓝方制造出来的第<span>n </span>个武士，编号也是<span>n</span>。</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="">武士在刚降生的时候有一个初始的生命值，生命值在战斗中会发生变化，如果生命值减少到<span>0</span>（生命值变为负数时应当做变为<span>0</span>处理），则武士死亡（消失）。</p><p class="MsoNormal" style="margin-bottom: 12pt;text-align:left;">武士可以拥有武器。武器有三种，<span>sword, bomb,</span>和<span>arrow</span>，编号分别为<span>0,1,2</span>。</p><p class="MsoNormal" style=""><span>sword</span>的攻击力是使用者当前攻击力的<span>20%(</span>去尾取整<span>)</span>。</p><p class="MsoNormal" style=""><span>bomb</span>的攻击力是使用者当前攻击力的<span>40%(</span>去尾取整<span>)</span>，但是也会导致使用者受到攻击，对使用者的攻击力是对敌人取整后的攻击力的<span>1/2(</span>去尾取整<span>)</span>。<span>Bomb</span>一旦使用就没了。</p><p class="MsoNormal" style=""><span>arrow</span>的攻击力是使用者当前攻击力的<span>30%(</span>去尾取整<span>)</span>。一个<span>arrow</span>用两次就没了。</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="">武士降生后就朝对方司令部走，在经过的城市如果遇到敌人（同一时刻每个城市最多只可能有<span>1</span>个蓝武士和一个红武士），就会发生战斗。战斗的规则是：</p><ol style="list-style-type:decimal"><li><p>在奇数编号城市，红武士先发起攻击</p></li><li><p>在偶数编号城市，蓝武士先发起攻击</p></li><li><p><span style="color: red">战斗开始前，双方先对自己的武器排好使用顺序，然后再一件一件地按顺序使用。编号小的武器，排在前面。若有多支<span>arrow</span>，用过的排在前面。排好序后，攻击者按此排序依次对敌人一件一件地使用武器。如果一种武器有多件，那就都要用上。每使用一件武器，被攻击者生命值要减去武器攻击力。如果任何一方生命值减为<span>0</span>或小于<span>0</span>即为死去。有一方死去，则战斗结束。</span></p></li><li><p><span style="color: red">双方轮流使用武器，甲用过一件，就轮到乙用。某一方把自己所有的武器都用过一轮后，就从头开始再用一轮。如果某一方没有武器了，那就挨打直到死去或敌人武器用完。武器排序只在战斗前进行，战斗中不会重新排序。</span></p></li><li><p>如果双方武器都用完且都还活着，则战斗以平局结束。如果双方都死了，也算平局。</p></li><li><p>有可能由于武士自身攻击力太低，而导致武器攻击力为<span>0</span>。攻击力为<span>0</span>的武器也要使用。如果战斗中双方的生命值和武器的状态都不再发生变化，则战斗结束，算平局。</p></li><li><p>战斗的胜方获得对方手里的武器。武士手里武器总数不超过<span>10</span>件。缴获武器时，按照武器种类编号从小到大缴获。如果有多件<span>arrow</span>，优先缴获没用过的。</p></li><li><p>如果战斗开始前双方都没有武器，则战斗视为平局。如果先攻击方没有武器，则由后攻击方攻击。</p></li></ol><p class="MsoNormal" style="margin-bottom: 12pt;text-align:left;">不同的武士有不同的特点。</p><p class="MsoNormal" style="">编号为<span>n</span>的<span>dragon</span>降生时即获得编号为<span>n%3 </span>的武器。<span>dragon</span>在战斗结束后，如果还没有战死，就会欢呼。</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="">编号为<span>n</span>的<span>ninjia</span>降生时即获得编号为<span>n%3 </span>和<span>(n+1)%3</span>的武器。<span>ninja </span>使用<span>bomb</span>不会让自己受伤。</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="">编号为<span>n</span>的<span>iceman</span>降生时即获得编号为<span>n%3 </span>的武器。<span>iceman</span>每前进一步，生命值减少<span>10%(</span>减少的量要去尾取整<span>)</span>。</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="">编号为<span>n</span>的<span>lion</span>降生时即获得编号为<span>n%3 </span>的武器。<span>lion </span>有“忠诚度”这个属性，其初始值等于它降生之后其司令部剩余生命元的数目。每前进一步忠诚度就降低<span>K</span>。忠诚度降至<span>0</span>或<span>0</span>以下，则该<span>lion</span>逃离战场<span>,</span>永远消失。但是已经到达敌人司令部的<span>lion</span>不会逃跑。<span>lion</span>在己方司令部可能逃跑。</p><p class="MsoNormal" style="margin-bottom: 12pt;text-align:left;"><span> </span></p><p class="MsoNormal" style="margin-bottom: 12pt;text-align:left;"><span style="color: red">wolf</span><span style="color: red">降生时没有武器，但是在战斗开始前会抢到敌人编号最小的那种武器。如果敌人有多件这样的武器，则全部抢来。Wolf手里武器也不能超过10件。如果敌人arrow太多没法都抢来，那就先抢没用过的。如果敌人也是<span>wolf</span>，则不抢武器。</span></p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="">以下是不同时间会发生的不同事件：</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="">在每个整点，即每个小时的第<span>0</span>分， 双方的司令部中各有一个武士降生。</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="">红方司令部按照<span>iceman</span>、<span>lion</span>、<span>wolf</span>、<span>ninja</span>、<span>dragon </span>的顺序制造武士。</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="">蓝方司令部按照<span>lion</span>、<span>dragon</span>、<span>ninja</span>、<span>iceman</span>、<span>wolf </span>的顺序制造武士。</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="">制造武士需要生命元。</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="">制造一个初始生命值为<span>m </span>的武士，司令部中的生命元就要减少<span>m </span>个。</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="">如果司令部中的生命元不足以制造某本该造的武士，那就从此停止制造武士。</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="">在每个小时的第<span>5</span>分，该逃跑的<span>lion</span>就在这一时刻逃跑了。</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="">在每个小时的第<span>10</span>分：所有的武士朝敌人司令部方向前进一步。即从己方司令部走到相邻城市，或从一个城市走到下一个城市。或从和敌军司令部相邻的城市到达敌军司令部。</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="">在每个小时的第<span>35</span>分：在有<span>wolf</span>及其敌人的城市，<span>wolf</span>要抢夺对方的武器。<span style="color:red"> </span></p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="">在每个小时的第<span>40</span>分：在有两个武士的城市，会发生战斗。<span style="color:red"> </span></p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="">在每个小时的第<span>50</span>分，司令部报告它拥有的生命元数量。</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="">在每个小时的第<span>55</span>分，每个武士报告其拥有的武器情况。</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="">武士到达对方司令部后就算完成任务了，从此就呆在那里无所事事。 </p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style=""><span style="color: red">任何一方的司令部里若是出现了敌人，则认为该司令部已被敌人占领。</span></p><p class="MsoNormal" style="">任何一方的司令部被敌人占领，则战争结束。战争结束之后就不会发生任何事情了。</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="">给定一个时间，要求你将从<span>0</span>点<span>0</span>分开始到此时间为止的所有事件按顺序输出。事件及其对应的输出样例如下：</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style=""><span>1) </span>武士降生</p><p class="MsoNormal" style="">输出样例：<span>000:00 blue dragon 1 born </span></p><p class="MsoNormal" style="">表示在<span>0</span>点<span>0</span>分，编号为<span>1</span>的蓝魔<span>dragon</span>武士降生</p><p class="MsoNormal" style="margin-bottom: 12pt;text-align:left;"><span> </span></p><p class="MsoNormal" style="margin-bottom: 12pt;text-align:left;">如果造出的是<span>lion</span>，那么还要多输出一行，例<span>:</span></p><p class="MsoNormal" style="margin-bottom: 12pt;text-align:left;">000:00 blue lion 1 born</p><p class="MsoNormal" style="margin-bottom: 12pt;text-align:left;">Its loyalty is 24</p><p class="MsoNormal" style="">表示该<span>lion</span>降生时的忠诚度是<span>24</span></p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style=""><span>2) lion</span>逃跑</p><p class="MsoNormal" style="">输出样例：<span>000:05 blue lion 1 ran away </span></p><p class="MsoNormal" style="">表示在<span>0</span>点<span>5</span>分，编号为<span>1</span>的蓝魔<span>lion</span>武士逃走</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style=""><span>3) </span>武士前进到某一城市</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="margin-left:21.0pt">输出样例：</p><p class="MsoNormal" style="margin-left:21.0pt"><br></p><p class="MsoNormal" style="margin-left:21.0pt">000:10 red iceman 1 marched to city 1 with 20 elements and force 30</p><p class="MsoNormal" style="">表示在<span>0</span>点<span>10</span>分，红魔<span>1</span>号武士<span>iceman</span>前进到<span>1</span>号城市，此时他生命值为<span>20,</span>攻击力为<span>30</span></p><p class="MsoNormal" style="">对于<span>iceman,</span>输出的生命值应该是变化后的数值</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style=""><span>4) wolf</span>抢敌人的武器</p><p class="MsoNormal" style=""><span>000:35 blue wolf 2 took 3 bomb from red dragon 2 in city 4</span></p><p class="MsoNormal" style="">表示在<span>0</span>点<span>35</span>分，<span>4</span>号城市中，红魔<span>1</span>号武士<span>wolf </span>抢走蓝魔<span>2</span>号武士<span>dragon 3</span>个<span>bomb</span>。为简单起见，武器不写复数形式</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style=""><span>5) </span>报告战斗情况</p><p class="MsoNormal" style="">战斗只有<span>3</span>种可能的输出结果：</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style=""><span>000:40 red iceman 1 killed blue lion 12 in city 2 remaining 20 elements </span></p><p class="MsoNormal" style="">表示在<span>0</span>点<span>40</span>分，<span>1</span>号城市中，红魔<span>1</span>号武士<span>iceman </span>杀死蓝魔<span>12</span>号武士<span>lion</span>后，剩下生命值<span>20</span></p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style=""><span>000:40 both red iceman 1 and blue lion 12 died in city 2</span></p><p class="MsoNormal" style="">注意，把红武士写前面</p><p class="MsoNormal" style=""><span style="white-space: normal;">000:40<span style="white-space: normal;"> </span></span>both red iceman 1 and blue lion 12 were alive in city 2</p><p class="MsoNormal" style="">注意，把红武士写前面</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style=""><span>6) </span>武士欢呼</p><p class="MsoNormal" style="">输出样例：<span>003:40 blue dragon 2 yelled in city 4</span></p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style=""><span>7) </span>武士抵达敌军司令部</p><p class="MsoNormal" style="">输出样例：<span>001:10 red iceman 1 reached blue headquarter with 20 elements and force 30</span></p><p class="MsoNormal" style="">（此时他生命值为<span>20,</span>攻击力为<span>30</span>）对于<span>iceman,</span>输出的生命值和攻击力应该是变化后的数值</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style=""><span>8) </span>司令部被占领</p><p class="MsoNormal" style="">输出样例：<span>003:10 blue headquarter was taken</span></p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style=""><span>9)</span>司令部报告生命元数量</p><p class="MsoNormal" style=""><span>000:50 100 elements in red headquarter </span></p><p class="MsoNormal" style=""><span>000:50 120 elements in blue headquarter</span></p><p class="MsoNormal" style="">表示在<span>0</span>点<span>50</span>分，红方司令部有<span>100</span>个生命元，蓝方有<span>120</span>个</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style=""><span>10)</span>武士报告情况</p><p class="MsoNormal" style=""><span>000:55 blue wolf 2 has 2 sword 3 bomb 0 arrow and 7 elements</span></p><p class="MsoNormal" style="">为简单起见，武器都不写复数形式。<span>elements</span>一律写复数，哪怕只有1个</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="">交代武器情况时，次序依次是：<span>sword,bomb, arrow</span>。</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="">输出事件时：</p><p class="MsoNormal" style=""><span> </span></p><p class="MsoNormal" style="">首先按时间顺序输出；</p><p class="MsoNormal" style="">同一时间发生的事件，按发生地点从西向东依次输出<span>. </span>武士前进的事件<span>, </span>算是发生在目的地。</p><p class="MsoNormal" style="">在一次战斗中有可能发生上面的 <span>5 </span>至 <span>6 </span>号事件。这些事件都算同时发生，其时间就是战斗开始时间。一次战斗中的这些事件，序号小的应该先输出。</p><p class="MsoNormal" style="">两个武士同时抵达同一城市，则先输出红武士的前进事件，后输出蓝武士的。</p><p class="MsoNormal" style=""><span style="color: red">对于同一城市，同一时间发生的事情，先输出红方的，后输出蓝方的。</span></p><p class="MsoNormal" style="">显然，<span>8</span>号事件发生之前的一瞬间一定发生了<span>7</span>号事件。输出时，这两件事算同一时间发生，但是应先输出<span>7</span>号事件</p><p class="MsoNormal" style="">虽然任何一方的司令部被占领之后，就不会有任何事情发生了。但和司令部被占领同时发生的事件，全都要输出。</p><p><br></p></dd>
				
				
<dt>输入</dt>
		<dd>第一行是t,代表测试数据组数<br><br>每组样例共三行。<br><br>第一行，4个整数 M,N,K, T。其含义为：<br>每个司令部一开始都有M个生命元( 1 &lt;= M &lt;= 100000)<br>两个司令部之间一共有N个城市( 1 &lt;= N &lt;= 20 )<br>lion每前进一步，忠诚度就降低K。(0&lt;=K&lt;=100)<br>要求输出从0时0分开始，到时间T为止(包括T) 的所有事件。T以分钟为单位，0 &lt;= T &lt;= 6000<br><br>第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。它们都大于0小于等于200<br><br>第三行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的攻击力。它们都大于0小于等于200</dd>
		<dt>输出</dt>
		<dd>对每组数据，先输出一行：<br><br>Case n:<br><br>如对第一组数据就输出 Case 1:<br><br>然后按恰当的顺序和格式输出到时间T为止发生的所有事件。每个事件都以事件发生的时间开头，时间格式是“时: 分”，“时”有三位，“分”有两位。</dd>
		<dt>样例输入</dt>
		<dd><pre>1
20 1 10 400
20 20 30 10 20
5 5 5 5 5</pre></dd>
		<dt>样例输出</dt>
		<dd><pre>Case 1:
000:00 blue lion 1 born
Its loyalty is 10
000:10 blue lion 1 marched to city 1 with 10 elements and force 5
000:50 20 elements in red headquarter
000:50 10 elements in blue headquarter
000:55 blue lion 1 has 0 sword 1 bomb 0 arrow and 10 elements
001:05 blue lion 1 ran away
001:50 20 elements in red headquarter
001:50 10 elements in blue headquarter
002:50 20 elements in red headquarter
002:50 10 elements in blue headquarter
003:50 20 elements in red headquarter
003:50 10 elements in blue headquarter
004:50 20 elements in red headquarter
004:50 10 elements in blue headquarter
005:50 20 elements in red headquarter
005:50 10 elements in blue headquarter
</pre></dd>
				<dt>提示</dt>
		<dd>请注意浮点数精度误差问题。OJ上的编译器编译出来的可执行程序，在这方面和你电脑上执行的程序很可能会不一致。5 * 0.3 的结果，有的机器上可能是 15.00000001，去尾取整得到15,有的机器上可能是14.9999999，去尾取整后就变成14。因此,本题不要写 5 * 0.3，要写 5 * 3 / 10。</dd>
						<dt>来源</dt>
		<dd>Guo Wei</dd>
				</dl>