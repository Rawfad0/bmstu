// Compiled by ClojureScript 1.12.42 {:optimizations :none}
goog.provide('hello_world.core');
goog.require('cljs.core');
cljs.core.println.call(null,"Hello world!");
cljs.core.reverse.call(null,cljs.core.list(new cljs.core.Symbol(null,"a","a",-482876059,null),new cljs.core.Symbol(null,"b","b",-1172211299,null),new cljs.core.Symbol(null,"c","c",-122660552,null)));
cljs.core.reverse.call(null,cljs.core.List.EMPTY);
cljs.core.reverse.call(null,cljs.core.list(new cljs.core.Symbol(null,"a","a",-482876059,null),new cljs.core.Symbol(null,"b","b",-1172211299,null),cljs.core.list(new cljs.core.Symbol(null,"c","c",-122660552,null),cljs.core.list(new cljs.core.Symbol(null,"d","d",-682293345,null)))));
cljs.core.reverse.call(null,cljs.core.list(new cljs.core.Symbol(null,"a","a",-482876059,null)));
cljs.core.last.call(null,cljs.core.list(new cljs.core.Symbol(null,"a","a",-482876059,null),new cljs.core.Symbol(null,"b","b",-1172211299,null),new cljs.core.Symbol(null,"c","c",-122660552,null)));
cljs.core.last.call(null,cljs.core.list(new cljs.core.Symbol(null,"a","a",-482876059,null),new cljs.core.Symbol(null,"b","b",-1172211299,null),cljs.core.list(new cljs.core.Symbol(null,"c","c",-122660552,null))));
cljs.core.last.call(null,cljs.core.list(new cljs.core.Symbol(null,"a","a",-482876059,null)));
cljs.core.last.call(null,cljs.core.List.EMPTY);
cljs.core.last.call(null,cljs.core.list(cljs.core.list(new cljs.core.Symbol(null,"a","a",-482876059,null),new cljs.core.Symbol(null,"b","b",-1172211299,null),new cljs.core.Symbol(null,"c","c",-122660552,null))));
hello_world.core.get_last1 = (function hello_world$core$get_last1(lst){
return cljs.core.last.call(null,lst);
});
hello_world.core.get_last2 = (function hello_world$core$get_last2(lst){
return cljs.core.first.call(null,cljs.core.reverse.call(null,lst));
});
hello_world.core.del_last = (function hello_world$core$del_last(lst){
return cljs.core.reverse.call(null,cljs.core.next.call(null,cljs.core.reverse.call(null,lst)));
});
hello_world.core.swap_first_last = (function hello_world$core$swap_first_last(lst){
return cljs.core.concat.call(null,(new cljs.core.List(null,cljs.core.last.call(null,lst),null,(1),null)),cljs.core.reverse.call(null,cljs.core.next.call(null,cljs.core.reverse.call(null,cljs.core.next.call(null,lst)))),(new cljs.core.List(null,cljs.core.first.call(null,lst),null,(1),null)));
});
hello_world.core.is_palindrome = (function hello_world$core$is_palindrome(lst){
return cljs.core._EQ_.call(null,lst,cljs.core.reverse.call(null,lst));
});
hello_world.core.get_capital = (function hello_world$core$get_capital(table,contry){
return cljs.core.next.call(null,cljs.core.assoc.call(null,hello_world.core.country,table));
});
hello_world.core.roll = (function hello_world$core$roll(){
return (new cljs.core.List(null,(cljs.core.rand_int.call(null,(6)) + (1)),(new cljs.core.List(null,(cljs.core.rand_int.call(null,(6)) + (1)),null,(1),null)),(2),null));
});
hello_world.core.roll_sum = (function hello_world$core$roll_sum(roll){
return (cljs.core.first.call(null,roll) + cljs.core.second.call(null,roll));
});
hello_world.core.instawin_check = (function hello_world$core$instawin_check(roll){
return ((cljs.core._EQ_.call(null,hello_world.core.roll_sum.call(null,roll),(7))) || (cljs.core._EQ_.call(null,hello_world.core.roll_sum.call(null,roll),(11))));
});
hello_world.core.reroll_check = (function hello_world$core$reroll_check(roll){
return ((cljs.core._EQ_.call(null,hello_world.core.roll_sum.call(null,roll),(2))) || (cljs.core._EQ_.call(null,hello_world.core.roll_sum.call(null,roll),(12))));
});
hello_world.core.second_roll = (function hello_world$core$second_roll(r1,r2){
cljs.core.println.call(null,cljs.core.sequence.call(null,cljs.core.seq.call(null,cljs.core.concat.call(null,(new cljs.core.List(null,new cljs.core.Symbol("cljs.core","second","cljs.core/second",520555958,null),null,(1),null)),(new cljs.core.List(null,new cljs.core.Symbol("hello-world.core","rolled","hello-world.core/rolled",-493991311,null),null,(1),null)),(new cljs.core.List(null,cljs.core.first.call(null,r2),null,(1),null)),(new cljs.core.List(null,cljs.core.second.call(null,r2),null,(1),null))))));

if(hello_world.core.instawin_check.call(null,r2)){
return cljs.core.println.call(null,cljs.core.sequence.call(null,cljs.core.seq.call(null,cljs.core.concat.call(null,(new cljs.core.List(null,new cljs.core.Symbol("cljs.core","second","cljs.core/second",520555958,null),null,(1),null)),(new cljs.core.List(null,new cljs.core.Symbol("hello-world.core","player","hello-world.core/player",-242402639,null),null,(1),null)),(new cljs.core.List(null,new cljs.core.Symbol("hello-world.core","won","hello-world.core/won",1922790934,null),null,(1),null))))));
} else {
if(hello_world.core.reroll_check.call(null,r2)){
return hello_world.core.second_roll.call(null,r1,hello_world.core.roll.call(null));
} else {
if((hello_world.core.roll_sum.call(null,r1) < hello_world.core.roll_sum.call(null,r2))){
return cljs.core.println.call(null,cljs.core.sequence.call(null,cljs.core.seq.call(null,cljs.core.concat.call(null,(new cljs.core.List(null,hello_world.core.roll_sum.call(null,r1),null,(1),null)),(new cljs.core.List(null,new cljs.core.Symbol("cljs.core","<","cljs.core/<",1677496129,null),null,(1),null)),(new cljs.core.List(null,hello_world.core.roll_sum.call(null,r2),null,(1),null)),(new cljs.core.List(null,new cljs.core.Symbol("cljs.core","->","cljs.core/->",1488366311,null),null,(1),null)),(new cljs.core.List(null,new cljs.core.Symbol("cljs.core","second","cljs.core/second",520555958,null),null,(1),null)),(new cljs.core.List(null,new cljs.core.Symbol("hello-world.core","player","hello-world.core/player",-242402639,null),null,(1),null)),(new cljs.core.List(null,new cljs.core.Symbol("hello-world.core","won","hello-world.core/won",1922790934,null),null,(1),null))))));
} else {
if((hello_world.core.roll_sum.call(null,r1) > hello_world.core.roll_sum.call(null,r2))){
return cljs.core.println.call(null,cljs.core.sequence.call(null,cljs.core.seq.call(null,cljs.core.concat.call(null,(new cljs.core.List(null,hello_world.core.roll_sum.call(null,r1),null,(1),null)),(new cljs.core.List(null,new cljs.core.Symbol("cljs.core",">","cljs.core/>",2020535938,null),null,(1),null)),(new cljs.core.List(null,hello_world.core.roll_sum.call(null,r2),null,(1),null)),(new cljs.core.List(null,new cljs.core.Symbol("cljs.core","->","cljs.core/->",1488366311,null),null,(1),null)),(new cljs.core.List(null,new cljs.core.Symbol("cljs.core","first","cljs.core/first",-752535972,null),null,(1),null)),(new cljs.core.List(null,new cljs.core.Symbol("hello-world.core","player","hello-world.core/player",-242402639,null),null,(1),null)),(new cljs.core.List(null,new cljs.core.Symbol("hello-world.core","won","hello-world.core/won",1922790934,null),null,(1),null))))));
} else {
return hello_world.core.first_roll.call(null,hello_world.core.roll.call(null));

}
}
}
}
});
hello_world.core.first_roll = (function hello_world$core$first_roll(r1){
cljs.core.println.call(null,cljs.core.sequence.call(null,cljs.core.seq.call(null,cljs.core.concat.call(null,(new cljs.core.List(null,new cljs.core.Symbol("cljs.core","first","cljs.core/first",-752535972,null),null,(1),null)),(new cljs.core.List(null,new cljs.core.Symbol("hello-world.core","rolled","hello-world.core/rolled",-493991311,null),null,(1),null)),(new cljs.core.List(null,cljs.core.first.call(null,r1),null,(1),null)),(new cljs.core.List(null,cljs.core.second.call(null,r1),null,(1),null))))));

if(hello_world.core.instawin_check.call(null,r1)){
return cljs.core.println.call(null,cljs.core.sequence.call(null,cljs.core.seq.call(null,cljs.core.concat.call(null,(new cljs.core.List(null,new cljs.core.Symbol("cljs.core","first","cljs.core/first",-752535972,null),null,(1),null)),(new cljs.core.List(null,new cljs.core.Symbol("hello-world.core","player","hello-world.core/player",-242402639,null),null,(1),null)),(new cljs.core.List(null,new cljs.core.Symbol("hello-world.core","won","hello-world.core/won",1922790934,null),null,(1),null))))));
} else {
if(hello_world.core.reroll_check.call(null,r1)){
return hello_world.core.first_roll.call(null,hello_world.core.roll.call(null));
} else {
return hello_world.core.second_roll.call(null,r1,hello_world.core.roll.call(null));

}
}
});
hello_world.core.dice_game = (function hello_world$core$dice_game(){
return hello_world.core.first_roll.call(null,hello_world.core.roll.call(null));
});
hello_world.core.dice_game.call(null);

//# sourceMappingURL=core.js.map
