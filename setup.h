#!/bin/bash

# FIREFOX INSTALLATION --------------------------------------------------------

firefox_location=`find / -type f -name "firefox.desktop" 2>/dev/null | tail -1`
sed -i 's/\(^Exec=\).*$/\1\/home\/manjaro\/firefox\/firefox-bin\ %u/g' $firefox_location -e 's/\(^Icon=\).*$/\1\/home\/manjaro\/firefox\/firefox\.png/g' 
#sudo cp -R #/run/media//.mozilla $HOME 
sudo chown manjaro:manjaro $HOME/.mozilla 
cp -R /run/media/manjaro/0715-FFE6/kde/firefox $HOME 
sudo chmod +x ~/firefox/firefox
sudo chmod +x ~/firefox/firefox.bin
#cp /run/media/manjaro//firefox.png ~/firefox

#------------------------------------------------------------------------------

# MAWK INSTALLATION -----------------------------------------------------------

git clone https://aur.archlinux.org/mawk.git
cd mawk
pkgname=mawk
pkgver=1.3.4_20171017
url="http://invisible-island.net/mawk/"
source="http://invisible-island.net/datafiles/release/$pkgname.tar.gz"

wget "$source"
tar -xvzf *.tar.gz
cd $pkgname-${pkgver/_/-}
sed -ie 's/log()/log(1,0)/g' configure
sed -ie "s/trap  *0/trap  'exit 0' 0/g" test/*
./configure
make -j1
sudo make install

#------------------------------------------------------------------------------

# QT5BASE & CMAKE INSTALLATION ------------------------------------------------

wget http://archlinux.org/packages/extra/x86_64/qt5-base/download

echo "export PATH=$HOME/qt5/bin:$PATH" $HOME"/.bashrc"

#cp /run/media/manjaro//cmake-3.12.1-Linux-x86_64.tar.gz ~/
tar -xvzf cmake*
mv cmake-3.12.1-Linux-x86_64 cmake
sudo ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake
rm -rf cmake*.tar.gz

#------------------------------------------------------------------------------

# FONT INSTALLATION -----------------------------------------------------------

#cp -R /run/media/manjaro//awesome-terminal-fonts ~/
mkdir ~/.fonts
cp awesome-terminal-fonts/build/*.ttf ~/.fonts
cp awesome-terminal-fonts/build/*.sh ~/.fonts
fc-cache -fv ~/.fonts
sed -i 's/PragmataPro/Inconsolata+Awesome/g' ~/awesome-terminal-fonts/config/10-symbols.conf
mkdir -p ~/.config/fontconfig/conf.d
cp ~/awesome-terminal-fonts/config/10-symbols.conf ~/.config/fontconfig/conf.d
rm -rf ~/awesome-terminal-fonts

#cp -R /run/media/manjaro//Inconsolata ~/
cp ~/Inconsolata/complete/Inconsolata\ Nerd\ Font\ Complete.otf ~/.fonts
rm -rf ~/Inconsolata

wget https://github.com/powerline/powerline/raw/develop/font/PowerlineSymbols.otf
wget https://github.com/powerline/powerline/raw/develop/font/10-powerline-symbols.conf
[ -d "~/.local/share/fonts/" ] || mkdir -p ~/.local/share/fonts/
mv PowerlineSymbols.otf ~/.local/share/fonts/
fc-cache -vf ~/.local/share/fonts/
[ -d "~/.config/fontconfig/conf.d" ] || mkdir -p ~/.config/fontconfig/conf.d
mv 10-powerline-symbols.conf ~/.config/fontconfig/conf.d/

#------------------------------------------------------------------------------

# VIM INSTALLATION ------------------------------------------------------------

#cp -R /run/media/manjaro//vim ~/
cd vim
./configure --with-features=huge \
            --enable-multibyte \
	        --enable-python3interp=yes \
	        --with-python3-config-dir=/usr/lib/python3.6/config-3.6m-x86_64-linux-gnu \
	        --enable-cscope \
	        --prefix=/usr/local
cd src
make VIMRUNTIMEDIR=/usr/local/share/vim/vim81
sudo make install
cd ../..
rm -rf ~/vim
pip3 install --user neovim

echo "set nocompatible hidden laststatus=2
set backspace=indent,eol,start
syntax on
filetype plugin indent on
inoremap qq <ESC>
\" Map <leader> key to comma
let mapleader = ','
nmap <F3> :set nu! <CR>
nmap <leader><F3> : set rnu! <CR>

nnoremap gjj :tabprevious <CR>
nnoremap gkk :tabnext <CR>
set modelines=0
call plug#begin('~/.vim/plugged')

Plug 'autozimu/LanguageClient-neovim', {
    \ 'branch': 'next',
    \ 'do': 'bash install.sh',
    \ }

Plug 'Shougo/deoplete.nvim'
Plug 'roxma/nvim-yarp'
Plug 'roxma/vim-hug-neovim-rpc'

Plug 'scrooloose/nerdtree'
Plug 'majutsushi/tagbar'

Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'
Plug 'ryanoasis/vim-devicons'

call plug#end()

\"let g:LanguageClient_trace = 'verbose'
\"let $RUST_BACKTRACE = 'full'
\"let g:LanguageClient_autoStart = \"1\"
\"let g:LanguageClient_diagnosticsEnable = 1
\"let g:LanguageClient_trace = 1
\"set completefunc=LanguageClient#complete
\"set formatexpr=LanguageClient_textDocument_rangeFormatting()set nocompatible
\"let g:LanguageClient_loggingFile = '/tmp/LanguageClient.log'
\"let g:LanguageClient_loggingLevel = 'INFO'
let g:LanguageClient_serverStderr = '/tmp/LanguageServer.log'

set cot+=preview

let g:LanguageClient_serverCommands = {
    \ 'cpp': ['/run/media/manjaro/_home/home2/cquery/build/cquery', '--log-file=/tmp/cq.log'],
    \ 'c': ['/run/media/manjaro/_home/home2/cquery/build/cquery', '--log-file=/tmp/cq.log'],
    \ }

let g:LanguageClient_rootMarkers = {
\ 'cpp': ['*.cpp', 'build', 'compile_commands.json'],
\ 'c': ['*.c', 'build', 'compile_commands.json'],
\ }

let g:LanguageClient_loadSettings = 1 
let g:LanguageClient_settingsPath = expand('~/prog/settings.json')
set completefunc=LanguageClient#complete
set formatexpr=LanguageClient_textDocument_rangeFormatting()

nnoremap <silent> gh :call LanguageClient#textDocument_hover()<CR>
nnoremap <silent> gd :call LanguageClient#textDocument_definition()<CR>
nnoremap <silent> gr :call LanguageClient#textDocument_references()<CR>
nnoremap <silent> gs :call LanguageClient#textDocument_documentSymbol()<CR>
nnoremap <silent> <F2> :call LanguageClient#textDocument_rename()<CR>

let g:airline#extensions#tabline#enabled = 1
let g:airline_theme='papercolor'
let g:airline_powerline_fonts = 1

let g:deoplete#enable_at_startup = 1
let g:deoplete#enable_refresh_always = 1

nmap <F8> :TagbarToggle<CR>
\" A buffer becomes hidden when it is abandoned
set hid

\" Ignore case when searching
set ignorecase

\" When searching try to be smart about cases 
set smartcase

\" Highlight search results
set hlsearch

\" Makes search act like search in modern browsers
set incsearch 
\" Add a bit extra margin to the left
\"set foldcolumn=1

\" => Moving around, tabs, windows and buffers

\" Map <Space> to / (search) and Ctrl-<Space> to ? (backwards search)
\" map <space> /
\" map <c-space> ?

function! ClangCheckImpl(cmd)
  if &autowrite | wall | endif
  echo \"Running \" . a:cmd . \" ...\"
  let l:output = system(a:cmd)
  cexpr l:output
  cwindow
  let w:quickfix_title = a:cmd
  if v:shell_error != 0
    cc
  endif
  let g:clang_check_last_cmd = a:cmd
endfunction

function! ClangCheck()
  let l:filename = expand('%')
  if l:filename =~ '\.\(cpp\|cxx\|cc\|c\)$'
    call ClangCheckImpl(\"clang-check \" . l:filename)
  elseif exists(\"g:clang_check_last_cmd\")
    call ClangCheckImpl(g:clang_check_last_cmd)
  else
  endif
endfunction

nmap <silent> <F5> :call ClangCheck()<CR><CR>

autocmd vimenter * NERDTree
map <C-n> :NERDTreeToggle<CR>

\" NERDTree
	let NERDTreeMinimalUI = 1
	let g:NERDTreeDirArrowExpandable = '🗀'
	let g:NERDTreeDirArrowCollapsible = '🗁'
	let g:NERDTreeHighlightFolders = 1
	let g:NERDTreeHighlightFoldersFullName = 1

set hidden
set noshowmode
set signcolumn=yes
set t_Co=256
set tabstop=8 softtabstop=0 expandtab shiftwidth=4 smarttab
highlight ColorColumn ctermbg=magenta
call matchadd('ColorColumn', '\%81v', 100)" >> ~/.vimrc

curl -fLo ~/.vim/autoload/plug.vim --create-dirs \
    https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
