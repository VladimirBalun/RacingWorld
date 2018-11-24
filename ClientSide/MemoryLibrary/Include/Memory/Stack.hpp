/*
 * Copyright 2018 Vladimir Balun
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

namespace Memory {

    template <class Type>
    class Stack
    {
    public:
        struct Node
        {
            Type  data;
            Node* next;
        };

        Stack(const Stack& other) = delete;
        explicit Stack() = default;
        void push(Node* newNode) noexcept;
        Node* pop() noexcept;
    private:
        Node* _head = nullptr;
    };

    template <class Type>
    void Memory::Stack<Type>::push(Node* newNode) noexcept
    {
        newNode->next = _head;
        _head = newNode;
    }

    template <class Type>
    auto Memory::Stack<Type>::pop() noexcept -> Node*
    {
        Node* top = _head;
        _head = _head->next;
        return top;
    }

}
