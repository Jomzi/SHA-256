Theory Of Algorithms
===
<blockquote>
<p> 
   Name - James O'Hanlon
   <br>
   ID - G00318662
</blockquote>

This Repository contains work from my 4th year theory of algorithms module for college. For this module we had to create the SHA256 Hash Algorithm in C by following a number of videos, provided by our lecturer. 



What is the SHA256 Hashing Algorithm?
---
SHA256 stands for Secure Hash Algorithm 256-bit and it’s used for cryptographic security.

Cryptographic hash algorithms produce irreversible and unique hashes. The larger the number of possible hashes, the smaller the chance that two values will create the same hash.

A hash is as a mathematical computer process that takes information and turns it into letters and numbers of a certain length. Hashing is used to make storing and finding information quicker because hashes are usually shorter and easier to find. Hashes also make information unreadable and so the original data can become confidential.

For example, “I like bitcoin” can be hashed and will equal: ad3e58f21b94f32dcadca6b71df4c31a18179f38011551a17a80d0ff065d22c5

If I were to capitalize the “b” in bitcoin, so it says, “I like Bitcoin” the hash will be completely different: d988ca30eaa88c0410ad6e48a5297c0d505dcee572f9884f1a6fa2cbc8dedc86

The number of possible combinations of letters and numbers produced by SHA 256 exceeds the number grains of sand on Earth! That makes guessing the data hidden within the hash virtually impossible. Hashes cannot be reversed, so the process is typically used for computer security.



How to run this project
---
To run this project you can either download a C compiler or set up a vitual machine on Google Cloud Platform. I will attach links to both below: 
<ul><li><a href="https://cloud.google.com/compute/docs/quickstart-linux/" rel="nofollow">Google Cloud Platform</a></li>
<li><a href="www.mingw.org/" rel="nofollow">C compiler</a></li></ul>

1. When you are setup in your C environment you can download this project or do a git clone from this repository and cd command into it.

2. You will need to install GGC, if it's not already there. To install GGC type the follow command: sudo apt-get install build-essential

3. To compile the program use: gcc -o sha256 sha256.c

4. Then excute it by using: ./sha256 testFile1.txt



Research
---
<ul><li><a href="https://www.youtube.com/watch?v=DMtFhACPnTY" rel="nofollow">Good video on how SHA256 works.</a></li>
<li><a href="https://decryptionary.com/dictionary/secure-hash-algorithm-256/" rel="nofollow">decryptionary.com</a></li>
<li><a href="https://github.com/B-Con/crypto-algorithms/blob/master/sha256.c" rel="nofollow">Helped me with the macros.</a></li>
<li><a href="https://passwordsgenerator.net/sha256-hash-generator/" rel="nofollow">Sha256 online generator.</a></li>  
</ul>


