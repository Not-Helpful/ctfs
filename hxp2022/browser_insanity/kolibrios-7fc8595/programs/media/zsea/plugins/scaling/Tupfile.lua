if tup.getconfig("NO_FASM") ~= "" then return end
tup.rule("scaling.asm", "fasm %f %o " .. tup.getconfig("KPACK_CMD"), "scaling.obj")
