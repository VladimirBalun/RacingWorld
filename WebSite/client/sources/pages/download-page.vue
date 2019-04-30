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
                    <button-component title="Скачать"></button-component>
                    <b>64-bit версия</b>
                    <button-component title="Скачать"></button-component>
                </section>
            </section>
        </div>
    </div>
</template>

<script>
    "use strict";

    import ButtonComponent from "../components/button-component";

    export default {
        components: {ButtonComponent},
        data() {
            return {};
        },
    }

</script>

<style scoped lang="sass">

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
        padding: 40px
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

</style>