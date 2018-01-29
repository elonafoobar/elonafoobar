cp 1.hsp 2.hsp
vim -es +'%s/txtvalid = 0\n\t*txtc = .*\n\t*txtc = rnd(txtc)\n\t*txt_select \(.*\)\n\t*tcol@txtfunc = 255, 255, 255/__txt__ \1' +'wq' 2.hsp
sed -i "" -e "/__txt__/s/, \"\"$//" 2.hsp
sed -i "" -e "/__txt__/s/, \"\"$//" 2.hsp
sed -i "" -e "/__txt__/s/, \"\"$//" 2.hsp
sed -i "" -e "/__txt__/s/, \"\"$//" 2.hsp
sed -i "" -e "/__txt__/s/, \"\"$//" 2.hsp
sed -i "" -e "/__txt__/s/, \"\"$//" 2.hsp
sed -i "" -e "/__txt__/s/, \"\"$//" 2.hsp
sed -i "" -e "/__txt__/s/, \"\"$//" 2.hsp
sed -i "" -e "/__txt__/s/, \"\"$//" 2.hsp
sed -i "" -e "/__txt__/s/, \"\"$//" 2.hsp
sed -i "" -e "s/__txt__/txt/" 2.hsp
