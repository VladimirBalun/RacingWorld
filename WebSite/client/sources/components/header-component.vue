<!--
- Copyright 2018 Vladimir Balun
-
- Licensed under the Apache License, Version 2.0 (the "License");
- you may not use this file except in compliance with the License.
- You may obtain a copy of the License at
-
-     http://www.apache.org/licenses/LICENSE-2.0
-
- Unless required by applicable law or agreed to in writing, software
- distributed under the License is distributed on an "AS IS" BASIS,
- WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
- See the License for the specific language governing permissions and
- limitations under the License.
-->

<template>

  <header>
      <nav class="main-menu">
          <router-link to="/" class="nav-button">RacingWorld</router-link>
          <router-link to="/news" class="nav-button">News</router-link>
          <router-link to="/forum" class="nav-button">Forum</router-link>
          <router-link to="/downloads" class="nav-button">Downloads</router-link>
      </nav>

      <div class="input">
          <a href="#" class="login">Login</a>
          <a href="#">Sign Up</a>
      </div>
  </header>

</template>

<script>

    "use strict";

    export default {};

</script>

<style scoped lang="sass">

  header
      background: rgba(0,0,0,.9)
      display: flex
      justify-content: space-between
      align-items: center
      padding: 0 15px 0 15px

  .main-menu a,
  .input a
      display: inline-block
      color: #a3a3a3
      padding: 15px 10px 15px 10px
      font-family: 'Roboto Condensed', sans-serif
      font-size: 18px
      text-decoration: none
      transition: 0.3s

  .main-menu a:hover,
  .input a:hover
      color: #ff0033

  .login
      position: relative

  .login:hover::before
      color: #a3a3a3

</style>