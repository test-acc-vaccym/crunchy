// Copyright 2017 The CrunchyCrypt Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "crunchy/internal/common/status_matchers.h"
#include "crunchy/key_management/crunchy_factory.h"
#include "crunchy/key_management/keyset_manager.h"
#include "crunchy/util/status.h"

namespace crunchy {

namespace {

TEST(BasicAeadTest, EncryptDecrypt) {
  // Create the keyset.
  auto keyset_handle = std::make_shared<KeysetHandle>();
  auto keyset_manager = ::absl::make_unique<KeysetManager>(keyset_handle);

  auto status_or_key_handle =
      keyset_manager->GenerateAndAddNewKey("aes-128-gcm");
  CRUNCHY_EXPECT_OK(status_or_key_handle.status());
  auto key_handle = status_or_key_handle.ValueOrDie();
  CRUNCHY_EXPECT_OK(keyset_manager->PromoteToPrimary(key_handle));

  // Use the keyset.
  auto status_or_crypter = MakeCrunchyCrypter(keyset_handle);
  CRUNCHY_ASSERT_OK(status_or_crypter.status());
  std::unique_ptr<CrunchyCrypter> crypter =
      std::move(status_or_crypter.ValueOrDie());

  const std::string plaintext = "banana";
  const std::string aad = "apple";

  auto status_or_ciphertext = crypter->Encrypt(plaintext, aad);
  CRUNCHY_ASSERT_OK(status_or_ciphertext.status());
  std::string ciphertext = status_or_ciphertext.ValueOrDie();
  auto status_or_decrypted = crypter->Decrypt(ciphertext, aad);
  CRUNCHY_ASSERT_OK(status_or_decrypted.status());
  std::string decrypted = status_or_decrypted.ValueOrDie();
  ASSERT_EQ(plaintext, decrypted);
}

}  // namespace

}  // namespace crunchy
