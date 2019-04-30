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
    <div class="btn-container">
        <div class="wrap-btn-container">
            <div class="btn-bg"></div>
            <button class="main-btn">{{title}}</button>
        </div>
    </div>
</template>

<script>

    "use strict";

    export default {
        props : ["title"],
        data() {
            return {};
        },
    }
</script>

<style scoped lang="sass">

    button:hover
        cursor: pointer

    button
        outline: none !important
        border: none
        background: transparent

    .btn-container
        display: -moz-box
        display: -ms-flexbox
        display: -webkit-box
        display: -webkit-flex
        display: flex
        flex-wrap: wrap
        justify-content: center
        padding: 5px 0 35px 0

    .wrap-btn-container
        width: 100%
        display: block
        position: relative
        z-index: 1
        border-radius: 25px
        overflow: hidden
        margin: 0 auto

    .btn-bg
        position: absolute
        z-index: -1
        width: 300%
        height: 100%
        background: #a64bf4
        background: -o-linear-gradient(to right, #ff0100, #2c0000, #ff0100, #2c0000)
        background: -moz-linear-gradient(to right, #ff0100, #2c0000, #ff0100, #2c0000)
        background: -webkit-linear-gradient(to right, #ff0100, #2c0000, #ff0100, #2c0000)
        background: linear-gradient(to right, #ff0100, #2c0000, #ff0100, #2c0000)
        top: 0
        left: -100%
        -webkit-transition: all 0.4s
        -o-transition: all 0.4s
        -moz-transition: all 0.4s
        transition: all 0.4s

    .main-btn
        font-size: 15px
        color: #fff
        line-height: 1.2
        text-transform: uppercase
        display: -webkit-box
        display: -webkit-flex
        display: -moz-box
        display: -ms-flexbox
        display: flex
        justify-content: center
        align-items: center
        padding: 0 20px
        width: 100%
        height: 50px


    .wrap-btn-container:hover .btn-bg
        left: 0
</style>