syntax on
filetype plugin indent on
set ts=2 sts=2 sw=2 et ai si
set rnu
call plug#begin()

Plug 'jiangmiao/auto-pairs'
Plug 'neoclide/coc.nvim'
Plug 'gruvbox-community/gruvbox'
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'
Plug 'preservim/nerdtree'

call plug#end()

" use <tab> to trigger completion and navigate to the next complete item
function! CheckBackspace() abort
  let col = col('.') - 1
   return !col || getline('.')[col - 1]  =~# '\s'
    endfunction

    inoremap <silent><expr> <Tab>
          \ coc#pum#visible() ? coc#pum#next(1) :
                \ CheckBackspace() ? "\<Tab>" :
                      \ coc#refresh()

set termguicolors
colo gruvbox

inoremap <c-b> <Esc>:NERDTreeToggle<cr>
nnoremap <c-b> <Esc>:NERDTreeToggle<cr>
map <c-k> :call CocAction('format')<cr>
