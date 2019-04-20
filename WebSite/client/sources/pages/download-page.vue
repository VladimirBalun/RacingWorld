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
    <div id="app">
        <div class="main-container">
            <section class="info">
                <b>Минимальные системные требования</b>
                <ul>
                    <li>CPU:     Pentium III or AMD K6</li>
                    <li>RAM:     100MB</li>
                    <li>OpenGL:  Version 3.3</li>
                    <li>OS:	 Windows 7, Windows 8, Windows 10</li>
                    <li>Store:	 500MB available space</li>
                    <li>Network: Broadband Internet connection</li>
                </ul><br>
                <b>Рекомендуемые системные требования</b>
                <ul>
                    <li>CPU:     Pentium III or AMD K6</li>
                    <li>RAM:     100MB</li>
                    <li>OpenGL:  Version 3.3</li>
                    <li>OS:	 Windows 7, Windows 8, Windows 10</li>
                    <li>Store:	 500MB available space</li>
                    <li>Network: Broadband Internet connection</li>
                </ul>
            </section>
            <section class="dwlogo">
                <section class="logo">
                    <img src="https://github.com/VladimirBalun/RacingWorld/raw/develop/RacingWorld.png">
                </section>
                <section class="dw-btns">
                    <b>32-bit версия</b>
                    <div class="btn-container">
                        <div class="wrap-btn-container">
                            <div class="btn-bg"></div>
                            <button class="dwn-btn" @click="get32">Скачать</button>
                        </div>
                    </div>
                    <b>64-bit версия</b>
                    <div class="btn-container">
                        <div class="wrap-btn-container">
                            <div class="btn-bg"></div>
                            <button class="dwn-btn" @click="get64">Скачать</button>
                        </div>
                    </div>
                </section>
            </section>
        </div>
    </div>

</template>

<script>

    "use strict";

    export default {
        data() {
            return {
                downloadURL32: "/file32.exe",
                downloadURL64: "/file64.exe"
            }
            },
        methods: {
            get32: function () {
                return location.href = this.downloadURL32;
            },
            get64: function () {
                return location.href = this.downloadURL64;
            }
        }


        };

</script>

<style scoped lang="sass">

    font-face
        font-family: sans-serif
        src: url("https://fonts.googleapis.com/css?family=Roboto")

    button:hover
        cursor: pointer

    button
        outline: none!important
        border: none
        background: transparent

    #app
        display: flex
        display: -webkit-box
        display: -webkit-flex
        display: -moz-box
        display: -ms-flexbox
        justify-content: center
        box-sizing: border-box

    .main-container
        background: #fff
        border-radius: 7px
        transition: all 0.2s
        width: 1024px
        margin: 40px 0
        padding: 20px
        display: -webkit-box
        display: -webkit-flex
        display: -moz-box
        display: -ms-flexbox
        display: flex
        justify-content: center
        box-shadow: 0px 5px 10px rgba(0, 0, 0, 0.2), -5px -5px 10px rgba(0, 0, 0, 0.1)
        font: 300 16px/22px "Roboto", "Open Sans", "Helvetica Neue", Helvetica, Arial, sans-serif;

    .info
        width: 60%
        height: 500px
        margin: 0 2%
        padding: 30px 0px 30px 77px
        text-align: left

    .info b
        line-height: 33px

    .info li
        padding: 3px

    .dwlogo
        width: 30%
        height: 500px

    .logo img
        width: 100%

    .dw-btns
        box-sizing: border-box
        width: 100%
        height: 65%
        border-radius: 10px
        overflow: hidden
        padding: 20px 5px
        margin-top: 10px
        box-shadow: 0px 5px 10px rgba(0, 0, 0, 0.1)
        text-align: center
        line-height: 44px
        font-weight: 500

    .btn-container
        display: -webkit-box
        display: -webkit-flex
        display: -moz-box
        display: -ms-flexbox
        display: flex
        flex-wrap: wrap
        justify-content: center
        padding: 5px 0px 35px 0px

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
        background: -webkit-linear-gradient(right, #ff0100, #2c0000, #ff0100, #2c0000)
        background: -o-linear-gradient(right, #ff0100, #2c0000, #ff0100, #2c0000)
        background: -moz-linear-gradient(right, #ff0100, #2c0000, #ff0100, #2c0000)
        background: linear-gradient(right, #ff0100, #2c0000, #ff0100, #2c0000)
        top: 0
        left: -100%
        -webkit-transition: all 0.4s
        -o-transition: all 0.4s
        -moz-transition: all 0.4s
        transition: all 0.4s

    .dwn-btn
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