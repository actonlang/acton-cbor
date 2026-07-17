void acton_cborQ_libQ___ext_init__() {
}

double acton_cborQ__decode_float16(B_bytes data) {
    uint64_t half = (data->str[0] << 8) + data->str[1];
    unsigned exp = (half >> 10) & 0x1f;
    uint64_t mant = half & 0x3ff;
    double val;

    if (exp == 0) val = ldexp(mant, -24);
    else if (exp != 31) val = ldexp(mant + 1024, exp - 25);
    else val = mant == 0 ? INFINITY : NAN;
    return half & 0x8000 ? -val : val;
}

double acton_cborQ__decode_float32(B_bytes data) {
    uint32_t ret = 0;

    for (int i = 0; i < 4; ++i) {
        ret |= (uint32_t)data->str[i] << (8 * (3 - i));
    }

    return ret;
}

double acton_cborQ__decode_float64(B_bytes data) {
    uint64_t ret = 0;

    for (int i = 0; i < 8; ++i) {
        ret |= (uint64_t)data->str[i] << (8 * (7 - i));
    }

    return ret;
}
