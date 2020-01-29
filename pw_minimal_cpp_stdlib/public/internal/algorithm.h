// Copyright 2020 The Pigweed Authors
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not
// use this file except in compliance with the License. You may obtain a copy of
// the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations under
// the License.
#pragma once

#include <type_traits>

namespace std {

template <typename T>
constexpr const T& min(const T& lhs, const T& rhs) {
  return (rhs < lhs) ? rhs : lhs;
}

template <typename T>
constexpr const T& max(const T& lhs, const T& rhs) {
  return (lhs < rhs) ? rhs : lhs;
}

template <typename T>
constexpr T&& forward(remove_reference_t<T>& value) {
  return static_cast<T&&>(value);
}

template <typename T>
constexpr T&& forward(remove_reference_t<T>&& value) {
  return static_cast<T&&>(value);
}

}  // namespace std
