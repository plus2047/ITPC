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
    if (x < 0) {
      (((1L << 62) % mod) * 4 % mod + x % mod + mod) % mod
    } else {
      x % mod
    }
  }
}

object ProtobufWithJava {
  // protobuf convert unsigned int value into java signed int value
  // we need to use those two function to convert it back
  val intBound: BigInt = BigInt(2).pow(32)
  val longBound: BigInt = BigInt(2).pow(64)

  def toUnsigned(x: Long): String = {
    if (x >= 0) {
      x.toString
    } else {
      (BigInt(x) + longBound).toString
    }
  }

  def toUnsigned(x: Int): String = {
    if (x >= 0) {
      x.toString
    } else {
      (BigInt(x) + intBound).toString
    }
  }

  def hashMod(input: String, mod: Long): String = {
    val x = Hashing
      .farmHashFingerprint64()
      .hashString(input, Charsets.UTF_8)
      .asLong()
    if (x < 0) {
      ((BigInt(x) + longBound) % mod).toString
    } else {
      (x % mod).toString
    }
  }
}
