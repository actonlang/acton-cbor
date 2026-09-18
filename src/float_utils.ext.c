void acton_cborQ_float_utilsQ___ext_init__() {
}

double acton_cborQ_float_utilsQ_decode_float16(uint64_t arg) {
    unsigned exp = (arg >> 10) & 0x1f;
    uint64_t mant = arg & 0x3ff;
    double val;

    if (exp == 0) val = ldexp(mant, -24);
    else if (exp != 31) val = ldexp(mant + 1024, exp - 25);
    else val = mant == 0 ? INFINITY : NAN;
    return arg & 0x8000 ? -val : val;
}

double acton_cborQ_float_utilsQ_decode_float32(uint64_t arg) {
    uint32_t int32 = (uint32_t)arg;
    float float32;
    memcpy(&float32, &int32, sizeof(float));
    double ret = float32;
    return ret;
}

double acton_cborQ_float_utilsQ_decode_float64(uint64_t arg) {
    double ret;
    memcpy(&ret, &arg, sizeof(double));
    return ret;
}

B_tuple acton_cborQ_float_utilsQ_decompose_float(double arg) {
    uint64_t int64;

    uint64_t sign;
    uint64_t exp;
    uint64_t mant;

    B_tuple ret;

    memcpy(&int64, &arg, sizeof(double));

    sign = (int64 & 0x8000000000000000) >> 63;
    exp = (int64 & 0x7ff0000000000000) >> 52;
    mant = (int64 & 0x000fffffffffffff);

    ret = $NEWTUPLE(3, toB_u64(sign), toB_u64(exp), toB_u64(mant));
    return ret;
}
