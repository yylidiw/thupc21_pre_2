{{ self.title() }}

{{ s('background') }}

*那女孩对我说*

*代价为十辆铲车*

{{ s('description') }}

小E喜欢和老师变换着花样玩牌。最近，他们又发明了一种叫做“狗蛋和二五仔”的玩法。

规则是这样的：

游戏开始时小E和老师各有 $20$ 点体力值，手上各有 $2$ 张牌。所有的牌是完全相同的。每个玩家的面前都可以放置牌，开始时双方面前没有任何牌。

双方轮流进行操作。玩家在每个自己的回合开始时先抽一张牌。”抽一张牌“的操作指的是，如果手上的牌的数量小于 $3$ 张，则再抓一张牌放在手上；如果手上恰好有 $3$ 张牌，则不能再抓牌。操作分为 $4$ 种类型。

- 技能。让自己的体力值 $-2$ ，然后抽一张牌。

- 攻击。具体地，玩家可以选择一张放在自己面前的**本回合还未攻击过**的牌，选择对方面前的一张牌同归于尽，或者选择一张放在自己面前的**本回合还未攻击过**的牌，让对方的体力值 $-3$ 。如果是后者，则将这张选择的牌标记为已攻击。

- 打牌。如果你面前的牌的数量小于 $4$ 张，且手上有牌才能进行此操作。先进行下面的过程 $3$ 次：

  - 随机选择一个角色，让它的体力值 $-1$ 。这个角色可以是自己、对方或者某一方面前的一张牌。如果双方场上的牌一共有 $m$ 张，那么选择到任何一个角色的概率为 $\frac{1}{m+2}$ 。 如果该角色是一张牌且体力值变为了 $0$ ，那么将它摧毁；如果该角色是一个玩家且体力值变为了 $0$ ，那么该玩家直接输掉游戏。

    在进行完 $3$ 次后将手上的一张牌放在自己面前。牌的体力值为 $2$ 。这张牌在本回合中被认为已攻击过。

- 结束回合，接下来轮到对方的回合。

一回合中，玩家可以进行多次操作，但是技能和打牌的操作次数之和不能超过 $O$ 。除了结束回合，这些操作没有顺序限制，比如你可以先打一张牌，然后使用技能，然后再打一张牌。在结束回合之前，玩家需要进行至少一次任意的操作才能结束回合。

在任何时刻如果有玩家的体力值小于或等于 $0$ ，那么该玩家输掉游戏。

游戏进行了几个回合后，现在轮到了小E的回合开始前。小E想让你帮他分析，如果双方都采用最优策略，那么现在自己赢的概率是多少。

{{ s('input format') }}

第一行一个正整数 $T$，表示数据组数。

对于每组数据，第一行两个正整数 $E,S$ ，分别表示小E和老师现在的体力值。保证 $1\le E,S\le 15$ 。

第二行一个非负整数 $c$，然后跟着 $c$ 个正整数 $a_1,\cdots,a_c$ ，表示老师面前有 $c$ 张牌，它们的体力值分别为 $a_1,\cdots,a_c$ 。保证 $0\le c \le 4$，$\forall~1\le i \le c,1\le a_i \le 2$ 。

第三行一个非负整数 $p$ ，然后跟着 $p$ 个正整数 $e_1,\cdots,e_p$ ，表示小E面前有 $p$ 张牌，它们的体力值分别为 $e_1,\cdots,e_p$ 。保证 $0\le e\le 4$，$\forall~1\le i\le c,1\le e_i\le 2$ 。

在你到来之前老师可能作了弊，所以你不需要判断输入的情况是否真的是游戏进行了几个回合后的情况。

{{ s('output format') }}

对于每组数据输出一行一个实数，表示小E在双方采用最优决策时获胜的概率。你的输出的和标准答案的相对误差或绝对误差不超过 $10^{-6}$ 时算作正确。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

回合开始，小E抽一张牌。此时小E手上有 $2$ 张牌，双方的面前都没有牌。双方的体力值均为 $1$ 。这时，最优策略下，小E不能使用技能，因为使用后会因为自己的体力值小于等于 $0$ 而输掉游戏；小E不能攻击，因为自己面前没有牌；小E也不能结束回合，因为本回合他还没有进行任何操作。所以小E的最优策略是打一张牌，这时会随机选到小E或者老师中的一个角色，让他体力值 $-1$ 然后输掉游戏。所以小E的获胜概率为 $0.5$ 。

{{ s('subtasks') }}

保证 $T\le 100000$ 。

{{ s('后记') }}

最后小E还是战胜了老师。

*“老师，我觉得是你术士玩得不够多。”*

*"现在都流行这么吹牛的吗？我术士有351493把胜场，全球都找不到一个术士胜场比我多的知道吗？"*