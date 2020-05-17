/*
 * Copyright (C) 2019 Siara Logics (cc)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @author Arundale R.
 *
 */
#ifndef unishox
#define unishox

extern int32_t unishox_compress(const char *in, size_t len, char *out, size_t len_out);
//extern int32_t unishox_decompress(const char *in, size_t len, char *out, size_t len_out);

class Unishox {

public:
  Unishox() {};

  int32_t unishox_decompress(const char *in, size_t len, char *out, size_t len_out);
  int32_t unishox_compress(const char *in, size_t len, char *out, size_t len_out);

private:

  // int32_t append_bits(unsigned int code, int clen);

  int32_t getBitVal(void);
  int32_t getCodeIdx(const char *code_type);
  int32_t readCount(void);
  void decodeRepeat(void);
  int32_t getNumFromBits(int32_t count);

  int32_t l;
  int32_t ol;
  int32_t bit_no;
  int32_t dstate;
  uint8_t state;
  uint8_t is_all_upper;

  // buffers
  const char *  in;
  size_t        len;
  char *        out;
  size_t        len_out;
};

#endif

