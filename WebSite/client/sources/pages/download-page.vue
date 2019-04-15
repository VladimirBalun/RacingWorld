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
        <h2><b>Минимальные системные требования</b></h2>
        <table>
            <tbody>
                <tr v-for="item in minimumSystemRequirements">
                    <td>{{ item.param }}:</td>
                    <td>{{ item.value }}</td>
                </tr>
            </tbody>
        </table>

        <h3><b>Скачать актуальную версию</b></h3>
        <a :href="downloadUrl">Скачать</a>
    </div>

</template>

<script>

    "use strict";

    export default {
        data() {
            return {
                minimumSystemRequirements: [
                    { param: "CPU", value: "Pentium III or AMD K6"},
                    { param: "RAM", value: "100MB"},
                    { param: "OpenGL", value: "Version 3.3"},
                    { param: "OS", value: "Windows 7, Windows 8, Windows 10"},
                    { param: "Store", value: "500MB available space"},
                    { param: "Network", value: "Broadband Internet connection"}],
                downloadUrl: "#index.html"
            }

            }
        };

</script>

<style scoped lang="sass">

    h1
        color: blue

</style>