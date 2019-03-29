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

"use strict";

const path = require("path");

const PRODUCTION_MODE = "production";
const DEVELOPMENT_MODE = "development";
const NODE_ENV = process.env.NODE_ENV || DEVELOPMENT_MODE;

const Webpack = require("webpack");
const VueLoaderPlugin = require("vue-loader/lib/plugin");
const HtmlWebpackPlugin = require("html-webpack-plugin");
const CopyWebpackPlugin = require("copy-webpack-plugin");

module.exports = {
    entry: {
        main: "./sources/index.js"
    },
    output: {
        path: path.resolve(__dirname, "./build"),
        publicPath: "./",
        filename: "index.js"
    },
    mode: NODE_ENV,
    devtool: NODE_ENV === DEVELOPMENT_MODE ? "eval" : null,
    watch: NODE_ENV === DEVELOPMENT_MODE,
    watchOptions: {
        aggregateTimeout: 100
    },
    performance: {
        hints: false
    },
    devServer: {
        hot: true,
        open: true,
        publicPath: "/"
    },
    module: {
        rules: [
            {
                test: /\.vue$/,
                loader: 'vue-loader'
            },
            {
                test: /\.scss$/,
                use: ['vue-style-loader','css-loader','sass-loader']
            },
            {
                test: /\.sass$/,
                use: ['vue-style-loader','css-loader','sass-loader?indentedSyntax']
            },
            {
                test: /\.js$/,
                loader: "babel-loader",
                include: [
                    path.resolve("scripts"),
                    path.resolve("node_modules/webpack-dev-server/client")
                ]
            },
            {
                test: /\.(png|jpg|gif|svg)$/,
                use: [{
                    loader: "file-loader",
                    options: {
                        name: "[name].[ext]",
                    }
                }],
            },
            {
                test: /\.css$/,
                use: [
                    {
                        loader: "vue-style-loader"
                    },
                    {
                        loader: "css-loader"
                    }
                ]
            }
        ],
    },
    plugins: [
        new Webpack.DefinePlugin({
            NODE_ENV: JSON.stringify(NODE_ENV),
            PRODUCTION_MODE: JSON.stringify(PRODUCTION_MODE),
            DEVELOPMENT_MODE: JSON.stringify(DEVELOPMENT_MODE)
        }),
        new HtmlWebpackPlugin({
            title: "RacingWorld",
            filename: "index.html",
            template: "./sources/index.html",
            inject: true
        }),
        new VueLoaderPlugin(),
        new CopyWebpackPlugin([
            {from: path.resolve(__dirname, "./sources/index.css")}
        ])
    ],
    resolve: {
        extensions: [".tsx", ".js", ".vue", ".json"],
        alias: {
            "vue$": "vue/dist/vue.esm.js",
            "@": path.resolve("src"),
        }
    }
};