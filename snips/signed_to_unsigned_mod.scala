
object SignedMod {
    def signedMod(x: Long, mod: Long): Long = {
        // Java VM has no unsigned number but some other language has.
        // So if we transform a unsigned number into java,
        // it may overflow into a negative numebr
        // this function transform back the overflowed number and return it's mod
        // =====
        // for negative long:
        // unsigned(x) == 2 ** 64 + x
        // unsigned(x) % mod == (2 ** 62 % mod * 4 % mod) + x % mod
        // (numeric theory)
        if(x < 0) {
            (((1L << 62) % mod) * 4 % mod + x % mod + mod) % mod
        } else {
            x % mod
        }
    }
}