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
    <div id="download-webpage">
        <div class="main-container">
            <section class="info">
                <h2 hidden>Информация и системные требования</h2>
                <h4><b>Минимальные системные требования</b></h4>
                <ul>
                    <li>CPU: Pentium III or AMD K6</li>
                    <li>RAM: 100MB</li>
                    <li>OpenGL: Version 3.3</li>
                    <li>OS: Windows 7, Windows 8, Windows 10</li>
                    <li>Store: 500MB available space</li>
                    <li>Network: Broadband Internet connection</li>
                </ul>
                <br>
                <h4><b>Рекомендуемые системные требования</b></h4>
                <ul>
                    <li>CPU: Pentium III or AMD K6</li>
                    <li>RAM: 100MB</li>
                    <li>OpenGL: Version 3.3</li>
                    <li>OS: Windows 7, Windows 8, Windows 10</li>
                    <li>Store: 500MB available space</li>
                    <li>Network: Broadband Internet connection</li>
                </ul>
            </section>
            <section class="download-logo">
                <h2 hidden>Логотип и кнопки загрузки</h2>
                <section class="logo">
                    <h2 hidden>Логотип продукта</h2>
                    <img alt="Logo" src="//github.com/VladimirBalun/RacingWorld/raw/develop/RacingWorld.png">
                </section>
                <section class="download-btns">
                    <h2 hidden>Кнопки для загрузки</h2>
                    <b>32-bit версия</b>
                    <section class="btn-container">
                        <div class="wrap-btn-container">
                            <div class="btn-bg"></div>
                            <button class="download-btn">Скачать</button>
                        </div>
                    </section>
                    <b>64-bit версия</b>
                    <section class="btn-container">
                        <div class="wrap-btn-container">
                            <div class="btn-bg"></div>
                            <button class="download-btn">Скачать</button>
                        </div>
                    </section>
                </section>
            </section>
        </div>
    </div>
</template>

<script>

    "use strict";

    export default {
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

    #download-webpage
        display: flex
        display: -moz-box
        display: -ms-flexbox
        display: -webkit-box
        display: -webkit-flex
        justify-content: center
        box-sizing: border-box

    .main-container
        background: #fff
        border-radius: 7px
        transition: all 0.2s
        width: 1024px
        margin: 40px 0
        padding: 40px 40px 20px 40px
        display: -moz-box
        display: -ms-flexbox
        display: -webkit-box
        display: -webkit-flex
        display: flex
        justify-content: center
        box-shadow: 0 5px 10px rgba(0, 0, 0, 0.2), -5px -5px 10px rgba(0, 0, 0, 0.1)
        font: 300 16px/22px "Roboto", "Open Sans", "Helvetica Neue", Helvetica, Arial, sans-serif;

    .info
        box-sizing: border-box
        width: 50%
        height: 550px
        padding: 10px 0 20px 4%
        margin: 0 20px 0 0

    .info b
        line-height: 33px

    .info li
        padding: 3px

    .download-logo
        display: block
        width: 40%
        height: 500px

    .logo
        width: 100%
        height: 40%

    .logo img
        width: 100%

    .download-btns
        box-sizing: border-box
        width: 90%
        height: 60%
        border-radius: 10px
        overflow: hidden
        padding: 20px 0 0 40px
        margin: 10px 231px 0 0
        text-align: center
        line-height: 44px
        font-weight: 500

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

    .download-btn
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