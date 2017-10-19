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

package com.google.security.crunchy;

import java.security.GeneralSecurityException;

/**
 * An interface for hybrid (aka asymmetric) decryption. Implementations may use authenticated
 * encryption and key versioning.
 */
public interface CrunchyHybridDecrypter {
  /**
   * Decrypts a payload.
   *
   * @param ciphertext The ciphertext to be decrypted.
   * @return The encrypted plaintext.
   * @throws GeneralSecurityException If the ciphertext failed an authentication check, if the key
   * identifier in the ciphertext cannot be found, or if the underlying crypto library returns an
   * error.
   */
  public byte[] decrypt(byte[] ciphertext) throws GeneralSecurityException;
}
