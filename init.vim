set nocompatible
set backspace=indent,eol,start
autocmd Filetype cpp setlocal tabstop=4

call plug#begin('~/.vim/plugged')

Plug 'autozimu/LanguageClient-neovim', {
    \ 'branch': 'next',
    \ 'do': 'install.sh',
    \ }

call plug#end()

let g:LanguageClient_serverCommands = {
    \ 'cpp': [expand('~/cquery/build/cquery'), '--log-file=/tmp/cq.log'],
    \ }

let g:LanguageClient_loadSettings = 1 " Use an absolute configuration path if you want system-wide settings
let g:LanguageClient_settingsPath = expand('~/.config/nvim/settings.json')
set completefunc=LanguageClient#complete
set formatexpr=LanguageClient_textDocument_rangeFormatting()

nnoremap <silent> gh :call LanguageClient#textDocument_hover()<CR>
nnoremap <silent> gd :call LanguageClient#textDocument_definition()<CR>
nnoremap <silent> gr :call LanguageClient#textDocument_references()<CR>
nnoremap <silent> gs :call LanguageClient#textDocument_documentSymbol()<CR>
nnoremap <silent> <F2> :call LanguageClient#textDocument_rename()<CR>
nnoremap <F5> :call LanguageClient_contextMenu()<CR>

let g:LanguageClient_trace = 'verbose'

set laststatus=2
set t_Co=256
set tabstop=4
set hidden
set signcolumn="yes"  
highlight ColorColumn ctermbg=magenta
call matchadd('ColorColumn', '\%81v', 100)
