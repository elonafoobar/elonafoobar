# Elona Foobar

* Elonaのヴァリアントの一つだ
* それはC++で作られている
* それはElona v1.22から派生した
* それはまだアルファ版だ
* それはLuaによる高い拡張性を持つ(予定) [\*\*\*\*+]
* それは真の国際化を実現する(予定) [\*\*\*\*+]
* それはマルチプラットフォームで動く [\*\*\*\*+] (現在WindowsとmacOSをサポート)



# How To Play

1. 本家開発版(v1.22)から`graphic`、`sound`の両フォルダをFoobarの`runtime/graphic`、`runtime/sound`へコピー
1. 本家開発版(v1.22)から`graphic/face1.bmp`をFoobarの`runtime/user/graphic/face1.bmp`へコピー
1. 適当なフォントファイルを`runtime/font`へ追加
1. `runtime/config.json`の`font1`と`font2`を先ほどのファイル名で書き換える。拡張子を含めることに注意
1. `runtime/ElonaFoobar`または`runtime/ElonaFoobar.exe`を実行


```json
{
  "font1": "Whatever font you like in Japanese",
  "font2": "Whatever font you like in Enligsh"
}
```



# How To Build/How to Contribute/License

README.md(英語)を参照
