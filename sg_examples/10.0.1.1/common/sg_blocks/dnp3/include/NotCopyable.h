/** @file NotCopyable.h
 *
 * @brief
 * Header file class representing base for not copyable classes
 *
 * @details
 * Contains declaration of a base class preventing object copying and moving
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_UTILS_NOTCOPYABLE_H_
#define STACK_UTILS_NOTCOPYABLE_H_

class NotCopyable {
public:
  NotCopyable() = default;
  NotCopyable(const NotCopyable&) = delete;
  NotCopyable(const NotCopyable&&) = delete;
  NotCopyable& operator=(const NotCopyable&) = delete;
  NotCopyable& operator=(const NotCopyable&&) = delete;
};

#endif /* STACK_UTILS_NOTCOPYABLE_H_ */
