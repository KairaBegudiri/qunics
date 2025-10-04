# QUNICS
QUNICS is un*x-like independent operating system. 
<hr>
<img width="1600" height="650" alt="Anatinus ve QUNICS" src="https://github.com/user-attachments/assets/942b0d27-63db-44d8-a15b-1924a7e18f97" />

## Screenshots
<img width="822" height="449" alt="resim" src="https://github.com/user-attachments/assets/0745882c-824d-4c89-afeb-bc059fb07380" />
QUNICS doesn't have a userland, so this isn't a bug or anything like that; it's expected. QUNICS has the POSIX standard, so a project that includes qunics and a userland (gnu, busybox, or similar) would be perfect.

## DevNote
- Our next goal is to combine the Qunics kernel with a userland (I'm planning to use GNU + Bash) and turn it into an operating system. Since this is for the future, I'm focusing on the kernel for now.
- After the stable version of the Qunics kernel is released, we plan to develop an operating system that uses the Qunics kernel. This operating system could have a completely independent userland or use only GNU + Bash. In any case, we named it QyzylOS (or Qyzyl GNU/Qunics).

## Build iso from source
```bash
git clone https://github.com/KairaBegudiri/qunics
cd qunics
make run
```
