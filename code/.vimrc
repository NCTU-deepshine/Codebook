set nu
set sw=4
set ts=4
set st=4
set bs=2
set cul
set ai
set ls=2
map <F5> gT
imap <F5> <ESC>gT
map <F6> gt
imap <F6> <ESC>gt
imap {<CR> {<CR><END><CR>}<UP><END>
au FileType cpp map <F9> <ESC>:w<CR>:!g++<Space>-Wall<Space>%&&./a.out<CR>
au FileType cpp imap <F9> <ESC>:w<CR>:!g++<Space>-Wall<Space>%&&./a.out<CR>
set encoding=UTF-8
