//
// Created by T0mmy on 13.01.2024.
//

#include "command.h"

std::vector<char> commandToBytes(Command command) {
    std::vector<char> bytes = {Int16ToBytes(uint16_t(command)).back()};
    return bytes;
}

int commandSize(Command command) {

    int res = 1;
    switch (command) {

        case Command::nop:
        case Command::aconst_null:
        case Command::iconst_m1:
        case Command::iconst_0:
        case Command::iconst_1:
        case Command::iconst_2:
        case Command::iconst_3:
        case Command::iconst_4:
        case Command::iconst_5:
        case Command::lconst_0:
        case Command::lconst_1:
        case Command::fconst_0:
        case Command::fconst_1:
        case Command::fconst_2:
        case Command::dconst_0:
        case Command::dconst_1:
        case Command::iload_0:
        case Command::iload_1:
        case Command::iload_2:
        case Command::iload_3:
        case Command::lload_0:
        case Command::lload_1:
        case Command::lload_2:
        case Command::lload_3:
        case Command::fload_0:
        case Command::fload_1:
        case Command::fload_2:
        case Command::fload_3:
        case Command::dload_0:
        case Command::dload_1:
        case Command::dload_2:
        case Command::dload_3:
        case Command::aload_0:
        case Command::aload_1:
        case Command::aload_2:
        case Command::aload_3:
        case Command::iaload:
        case Command::laload:
        case Command::faload:
        case Command::daload:
        case Command::aaload:
        case Command::baload:
        case Command::caload:
        case Command::saload:
        case Command::istore_0:
        case Command::istore_1:
        case Command::istore_2:
        case Command::istore_3:
        case Command::lstore_0:
        case Command::lstore_1:
        case Command::lstore_2:
        case Command::lstore_3:
        case Command::fstore_0:
        case Command::fstore_1:
        case Command::fstore_2:
        case Command::fstore_3:
        case Command::dstore_0:
        case Command::dstore_1:
        case Command::dstore_2:
        case Command::dstore_3:
        case Command::astore_0:
        case Command::astore_1:
        case Command::astore_2:
        case Command::astore_3:
        case Command::pop:
        case Command::pop2:
        case Command::dup:
        case Command::dup_x1:
        case Command::dup_x2:
        case Command::dup2:
        case Command::dup2_x1:
        case Command::dup2_x2:
        case Command::swap:
        case Command::iadd:
        case Command::ladd:
        case Command::fadd:
        case Command::dadd:
        case Command::isub:
        case Command::lsub:
        case Command::fsub:
        case Command::dsub:
        case Command::imul:
        case Command::lmul:
        case Command::fmul:
        case Command::dmul:
        case Command::idiv:
        case Command::ldiv:
        case Command::fdiv:
        case Command::ddiv:
        case Command::irem:
        case Command::lrem:
        case Command::frem:
        case Command::drem:
        case Command::ineg:
        case Command::lneg:
        case Command::fneg:
        case Command::dneg:
        case Command::ishl:
        case Command::lshl:
        case Command::ishr:
        case Command::lshr:
        case Command::iushr:
        case Command::lushr:
        case Command::iand:
        case Command::land:
        case Command::ior:
        case Command::lor:
        case Command::ixor:
        case Command::lxor:
        case Command::i2l:
        case Command::i2f:
        case Command::i2d:
        case Command::l2i:
        case Command::l2f:
        case Command::l2d:
        case Command::f2i:
        case Command::f2l:
        case Command::f2d:
        case Command::d2i:
        case Command::d2l:
        case Command::d2f:
        case Command::i2b:
        case Command::i2c:
        case Command::i2s:
        case Command::lcmp:
        case Command::fcmpl:
        case Command::fcmpg:
        case Command::dcmpl:
        case Command::dcmpg:
        case Command::ireturn:
        case Command::lreturn:
        case Command::freturn:
        case Command::dreturn:
        case Command::areturn:
        case Command::return_:
        case Command::arraylength:
        case Command::athrow:
            res = 1;
            break;

        case Command::bipush:
        case Command::ldc:
        case Command::iload:
        case Command::lload:
        case Command::fload:
        case Command::dload:
        case Command::aload:
        case Command::istore:
        case Command::lstore:
        case Command::fstore:
        case Command::dstore:
        case Command::astore:
        case Command::iastore:
        case Command::lastore:
        case Command::fastore:
        case Command::dastore:
        case Command::aastore:
        case Command::bastore:
        case Command::castore:
        case Command::sastore:
        case Command::jsr:
        case Command::newarray:
            res = 2;
            break;

        case Command::sipush:
        case Command::ldc_w:
        case Command::iinc:
        case Command::ifeq:
        case Command::ifne:
        case Command::iflt:
        case Command::ifge:
        case Command::ifgt:
        case Command::ifle:
        case Command::if_icmpeq:
        case Command::if_icmpne:
        case Command::if_icmplt:
        case Command::if_icmpge:
        case Command::if_icmpgt:
        case Command::if_icmple:
        case Command::if_acmpeq:
        case Command::if_acmpne:
        case Command::goto_:
        case Command::ret:
        case Command::getstatic:
        case Command::putstatic:
        case Command::getfield:
        case Command::putfield:
        case Command::invokevirtual:
        case Command::invokespecial:
        case Command::invokestatic:
        case Command::invokeinterface:
        case Command::invokedynamic:
        case Command::new_:
        case Command::anewarray:
        case Command::ifnull:
        case Command::ifnonnull:
        case Command::checkcast:
        case Command::instanceof:
        case Command::monitorenter:
        case Command::monitorexit:
            res = 3;
            break;


        case Command::wide:
            res = -1;
            break;
        case Command::multianewarray:
            res = 4;
            break;
        case Command::goto_w:
        case Command::jsr_w:
            res = 5;
            break;
    }

    return res;
}
