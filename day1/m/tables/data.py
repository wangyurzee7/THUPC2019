ret = [["测试点","$x$","$n$","$\\sum n^k$","完全二叉","$T$"]]
for datum in prob['data']:
    args = datum['args']
    row = [
        ','.join(map(str, datum['cases'])),
        "$= %s$" % tools.hn(args[0]),
        "$\\le %s$" % tools.hn(args[1]),
        "$\\sum n^{%s} \\le %s$" % (tools.hn(args[2]), tools.hn(args[5])),
        "Yes" if args[3] != 0 else "No",
        "$\\le %s$" % tools.hn(args[4])
    ]
    ret.append(row)
common.log.debug(u'输出调试信息')
return merge_ver(ret)
