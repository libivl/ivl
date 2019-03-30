/* This file is part of the ivl C++ library <http://image.ntua.gr/ivl>.
   A C++ template library extending syntax towards mathematical notation.

   Copyright (C) 2012 Yannis Avrithis <iavr@image.ntua.gr>
   Copyright (C) 2012 Kimon Kontosis <kimonas@image.ntua.gr>

   ivl is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License
   version 3 as published by the Free Software Foundation.

   Alternatively, you can redistribute it and/or modify it under the terms
   of the GNU General Public License version 2 as published by the Free
   Software Foundation.

   ivl is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   and a copy of the GNU Lesser General Public License along
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

#ifndef IVL_SAMPLES_CORE_TYPES_LIST_BEGIN_HPP
#define IVL_SAMPLES_CORE_TYPES_LIST_BEGIN_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace vocabulary {

using namespace ivl::types;

//-----------------------------------------------------------------------------

template <class T>
struct word { static char text[]; };

//-----------------------------------------------------------------------------

template <class S, class T>
S& operator<<(S& s, word <T>) { return s << word <T>::text; }

#define DEFINE_WORD(STRUCT, TEXT) \
struct STRUCT : public word <STRUCT> { }; \
template <> char word <STRUCT>::text[] = #TEXT; \

#define WORD(W) DEFINE_WORD(W, W)
#define _WORD(W) DEFINE_WORD(_##W, W)
#define __WORD(W) DEFINE_WORD(__##W, W)

//-----------------------------------------------------------------------------

typedef number <0> _0_;
typedef number <1> _1_;
typedef number <2> _2_;
typedef number <3> _3_;
typedef number <4> _4_;
typedef number <5> _5_;
typedef number <6> _6_;
typedef number <7> _7_;
typedef number <8> _8_;
typedef number <9> _9_;
typedef number <10> _10_;
typedef number <11> _11_;
typedef number <12> _12_;
typedef number <13> _13_;
typedef number <14> _14_;
typedef number <15> _15_;
typedef number <16> _16_;
typedef number <17> _17_;
typedef number <18> _18_;
typedef number <19> _19_;

//-----------------------------------------------------------------------------

typedef number <-1> _m1_;
typedef number <-2> _m2_;
typedef number <-3> _m3_;
typedef number <-4> _m4_;
typedef number <-5> _m5_;
typedef number <-6> _m6_;
typedef number <-7> _m7_;
typedef number <-8> _m8_;
typedef number <-9> _m9_;
typedef number <-10> _m10_;
typedef number <-11> _m11_;
typedef number <-12> _m12_;
typedef number <-13> _m13_;
typedef number <-14> _m14_;
typedef number <-15> _m15_;
typedef number <-16> _m16_;
typedef number <-17> _m17_;
typedef number <-18> _m18_;
typedef number <-19> _m19_;

//-----------------------------------------------------------------------------

__WORD(and)
_WORD(atom)
WORD(apples)
WORD(apple)
WORD(bacon)
WORD(bagels)
WORD(banana)
WORD(bean)
WORD(beans)
WORD(beef)
WORD(brandy)
WORD(bread)
WORD(butter)
WORD(bye)
WORD(carrot)
WORD(casserole)
WORD(cheese)
WORD(cherry)
WORD(chips)
WORD(chocolate)
WORD(chop)
WORD(chops)
WORD(chicken)
WORD(chickens)
WORD(chuck)
WORD(coffee)
WORD(could)
WORD(cream)
WORD(cup)
WORD(dessert)
WORD(duckling)
WORD(eat)
WORD(eggplant)
WORD(eggs)
WORD(eleven)
WORD(fat)
WORD(fish)
WORD(five)
WORD(flavored)
WORD(flying)
_WORD(for)
WORD(four)
WORD(fried)
WORD(fudge)
WORD(full)
WORD(good)
WORD(got)
WORD(grape)
WORD(gravy)
WORD(green)
WORD(had)
WORD(ham)
WORD(hamburger)
WORD(hamburgers)
WORD(hard)
WORD(heap)
WORD(hello)
WORD(help)
WORD(hick)
WORD(horseradish)
WORD(hot)
WORD(hotdog)
WORD(hotdogs)
WORD(house)
WORD(how)
WORD(ice)
__WORD(if)
_WORD(is)
WORD(jalapeno)
WORD(jelly)
WORD(just)
WORD(ketchup)
WORD(lamb)
WORD(large)
WORD(lasagna)
WORD(learn)
WORD(lemon)
WORD(lettuce)
WORD(light)
WORD(little)
WORD(liver)
WORD(low)
WORD(lox)
WORD(macaroni)
WORD(margarine)
WORD(mashed)
WORD(meat)
WORD(meatball)
WORD(milk)
WORD(mint)
WORD(more)
WORD(mozzarella)
WORD(much)
WORD(mushroom)
WORD(mustard)
WORD(need)
WORD(no)
WORD(oat)
WORD(of)
WORD(on)
__WORD(or)
WORD(orange)
WORD(oranges)
WORD(ounces)
_WORD(pair)
WORD(pea)
WORD(peach)
WORD(peaches)
WORD(peanut)
WORD(pear)
WORD(pears)
WORD(pecker)
WORD(peppers)
WORD(pickle)
WORD(pickles)
WORD(pie)
WORD(pieces)
WORD(pizza)
WORD(plum)
WORD(plums)
WORD(poached)
WORD(potato)
WORD(potatoes)
WORD(pounds)
WORD(prune)
WORD(prunes)
WORD(pumpkin)
WORD(raisin)
WORD(ravioli)
WORD(red)
WORD(relish)
WORD(rigatoni)
WORD(roast)
WORD(rye)
WORD(salad)
WORD(salami)
WORD(salsa)
WORD(salty)
WORD(sauce)
WORD(sauerkraut)
WORD(sausage)
WORD(scrambled)
WORD(seven)
WORD(sherbet)
WORD(sick)
WORD(soda)
WORD(some)
WORD(soured)
WORD(soy)
WORD(spaghetti)
WORD(split)
WORD(stewed)
WORD(strawberry)
WORD(sweet)
WORD(swing)
WORD(tacos)
WORD(tamales)
WORD(tastes)
WORD(tea)
_WORD(this)
WORD(to)
WORD(toast)
WORD(tomato)
WORD(tomatoes)
WORD(topping)
WORD(tuna)
WORD(vanilla)
WORD(very)
WORD(we)
WORD(wings)
_WORD(with)
WORD(wood)
WORD(would)

//-----------------------------------------------------------------------------

WORD(Jack)
WORD(Harry)
WORD(Mary)
WORD(Sprat)

}  // namespace vocabulary

//-----------------------------------------------------------------------------

#endif  // IVL_SAMPLES_CORE_TYPES_LIST_BEGIN_HPP
