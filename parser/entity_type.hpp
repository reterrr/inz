//
// Created by yhwach on 8/17/25.
//

#ifndef ENTITY_TYPE_HPP
#define ENTITY_TYPE_HPP

enum class entity_type {
  comment,
  expression,

  function, //as well as either simple function or lambda
  call, // invokable things like function, lambda, maybe some functor

  sys_call, // ????? do i even need this?

  if_block,
  while_block,
  for_block,
  do_while_block,
  match_block,

  struct_block, // ?
  enum_block, // ?

  comment_block // do i even need this?
};

#endif //ENTITY_TYPE_HPP
