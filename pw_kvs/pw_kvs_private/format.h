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

#include <cstddef>
#include <cstdint>
#include <cstring>

#include "pw_span/span.h"

namespace pw::kvs {

// In-flash header format.
struct EntryHeader {
  EntryHeader() = default;

  EntryHeader(uint32_t magic,
              span<const std::byte> checksum,
              size_t key_length,
              size_t value_length,
              uint32_t key_version)
      : magic_(magic),
        checksum_(0),
        key_value_length_(value_length << kValueLengthShift |
                          (key_length & kKeyLengthMask)),
        key_version_(key_version) {
    std::memcpy(&checksum_,
                checksum.data(),
                std::min(checksum.size(), sizeof(checksum_)));
  }

  span<const std::byte> DataForChecksum() const {
    return span(reinterpret_cast<const std::byte*>(this) +
                    offsetof(EntryHeader, key_value_length_),
                sizeof(*this) - offsetof(EntryHeader, key_value_length_));
  }

  uint32_t magic() const { return magic_; }
  span<const std::byte> checksum() const {
    return as_bytes(span(&checksum_, 1));
  }
  size_t key_length() const { return key_value_length_ & kKeyLengthMask; }
  size_t value_length() const { return key_value_length_ >> kValueLengthShift; }
  uint32_t key_version() const { return key_version_; }

 private:
  static constexpr uint32_t kKeyLengthMask = 0b111111;
  static constexpr uint32_t kValueLengthShift = 8;

  uint32_t magic_;
  uint32_t checksum_;
  // 0:5 key_len 8:31 value_len
  uint32_t key_value_length_;
  uint32_t key_version_;
};

static_assert(sizeof(EntryHeader) == 16, "EntryHeader should have no padding");

}  // namespace pw::kvs