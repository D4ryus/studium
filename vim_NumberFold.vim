" Function to fold text with numbered sections
function! NumberFold()
        let h = matchstr(getline(v:lnum), '^\d\+')
        if empty(h)
                return "="
        else
                return ">" . len(h)
        endif
endfunction
