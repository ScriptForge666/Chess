// Copyright 2026 Scriptforge
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//     http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
export module Error;
import std;

export namespace Error {
    enum class Code {
        InternalError = 1,
    };

    export std::string to_string(Code c) {
        return "E" + std::to_string(static_cast<int>(c)).insert(0, 3 - std::to_string(static_cast<int>(c)).length(), '0');
    }
}