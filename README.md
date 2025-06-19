# MINIGIT-DSA
An implementation of a lightweight version of Git that tracks changes to files, supports commits, branching, merging, and log history, without using external version control libraries.

### External Code Used
**SHA-1 Hashing**: This project uses a public domain SHA-1 implementation from(https://github.com/vog/sha1/blob/master/sha1.hpp) to stimulate Git's file tracking logic.

###Each Member's Role 
1. Bezawit Biazine: Core infrustructure; (int, blob and reference)
2. Elnathan Nigussie: Staging System; add command implementation
3. Iman Belete Commit Archtecture
4. Zafran Seid: History and navigation (implemented log and checkout)
5. Zuleyka Seid: Branching system (implemented merge and branch)
