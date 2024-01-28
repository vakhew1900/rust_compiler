//
// Created by T0mmy on 28.01.2024.
//

#include "classesnodes.h"
#include "semantics/rtl/RTLContainer.h"

int loopCnt = 0;
vector<ExprNode *> blockExprList;
vector<DataType> returnTypes;
vector<DataType> breakTypes;
map<string, set<string>> impl_set; // пиздец
vector<ItemNode *> not_completed;

// ------------------------  GetAllItems ------------------------------------
void Node::getAllItems(string className) {

}


void ProgramNode::getAllItems(std::string className) {

    this->classTableItem = ClassTableItem();
    classTableItem.classType = ClassTableItem::mod_;
    ClassTable::Instance()->addClass(className + "/" + ClassTable::moduleClassName, classTableItem);
    try {
        if (item_list != NULL) {
            for (auto elem: *item_list->items) {
                if (elem->item_type == ItemNode::function_ || elem->item_type == ItemNode::constStmt_) {
                    elem->curClassName = className + "/" + ClassTable::moduleClassName;
                    elem->getAllItems(className + "/" + ClassTable::moduleClassName);
                } else {
                    elem->getAllItems(className);
                }
            }
        }


        for (auto elem: not_completed) {
            elem->modifyInheritence();
        }

        this->addImpl(className, false);
        if (item_list != NULL) {

            for (auto elem: *item_list->items) {
                if (elem->item_type == ItemNode::function_ || elem->item_type == ItemNode::constStmt_)
                    elem->addDataTypeToDeclaration(className + "/" + ClassTable::moduleClassName);
                else
                    elem->addDataTypeToDeclaration(className);
            }
        }

        ClassTable::isCorrectTraitsImpl();
        ClassTable::isMainFunctionExist();
        ClassTable::makeMainForJavaFormat();
        ClassTable::checkClassNames();
    }
    catch (Exception e) {
        cerr << e.getMessage() << "\n";
    }
}

void ItemNode::getAllItems(std::string className) {
    auto classTable = ClassTable::Instance();
    try {
        switch (item_type) {
            case function_:
                this->methodTableItem = MethodTableItem();
                if (this->body != NULL) this->methodTableItem.isHasBody = true;
                if (this->visibility == pub) this->methodTableItem.isPub = true;
                if (ClassTable::Instance()->getClass(className).classType != ClassTableItem::trait_ &&
                    this->methodTableItem.isHasBody == false) {
                    throw Exception(Exception::NOT_IMPLEMICATION, *this->name + " NOT_IMPLEMICATION", this->line);
                }

                {
                    bool isSelf = (this->params->func_type == FuncParamListNode::self_ref
                                   || this->params->func_type == FuncParamListNode::self ||
                                   this->params->func_type == FuncParamListNode::mut_self_ref);

                    bool isHasNotMethod = ClassTable::Instance()->getClass(className).classType == ClassTableItem::mod_
                                          || ClassTable::Instance()->getClass(className).classType ==
                                             ClassTableItem::enum_;

                    if (isSelf && isHasNotMethod) {
                        throw Exception(Exception::NOT_A_METHOD, "function " + *this->name + " NOT_A_METHOD",
                                        this->line);
                    }
                }

                if ((this->params->func_type == FuncParamListNode::self_ref
                     || this->params->func_type == FuncParamListNode::self)
                    || this->params->func_type == FuncParamListNode::mut_self_ref) {
                    this->methodTableItem.isStatic = false;

                    if (this->params->func_type == FuncParamListNode::self_ref) {
                        this->methodTableItem.isRefSelf = true;
                    }
                }

                ClassTable::Instance()->addMethod(className, *this->name, this->methodTableItem);
                break;
            case constStmt_:
                this->fieldTableItem = FieldTableItem();
                if (this->expr != NULL) this->fieldTableItem.isInit = true;
                if (this->visibility == pub) this->fieldTableItem.isPub = true;
                if (this->fieldTableItem.isInit == false &&
                    ClassTable::Instance()->getClass(className).classType != ClassTableItem::trait_) {
                    throw Exception(Exception::NOT_IMPLEMICATION, *this->name + " NOT_DEFINED", this->line);
                }

                fieldTableItem.isConst = true;
                ClassTable::Instance()->addField(className, *this->name, this->fieldTableItem);
                break;
            case trait_: {
                this->classTableItem = ClassTableItem();
                classTableItem.classType = ClassTableItem::trait_;
                if (this->visibility == pub) this->classTableItem.isPub = true;
                ClassTable::Instance()->addClass(className + "/" + *this->name, classTableItem);
                if (this->items != NULL) {
                    for (auto elem: *this->items->items) {
                        if (elem->visibility == pub) {
                            throw Exception(Exception::PUB_NOT_PERMITTED,
                                            "pub` not permitted here because it's implied :" + *this->name + " " +
                                            *elem->name, this->line);
                        }
                        elem->visibility = pub;
                        elem->curClassName = className + "/" + *this->name;
                        elem->getAllItems(className + "/" + *this->name);

                        if (elem->item_type == ItemNode::function_
                            && elem->body == NULL) {
                        }

                        if (elem->item_type == ItemNode::constStmt_
                            && elem->expr == NULL) {
                            ClassTable::addAbstract(className + "/" + *this->name);
                        }
                    }
                }
                if (this->isHaveParent()) {
                    this->directory = className;
                    not_completed.push_back(this);
                }

            }
                break;
            case module_:
                this->classTableItem = ClassTableItem();
                classTableItem.classType = ClassTableItem::mod_;
                if (this->visibility == pub) this->classTableItem.isPub = true;
                ClassTable::Instance()->addClass(className + "/" + *this->name + "/" + ClassTable::moduleClassName,
                                                 classTableItem);

                if (this->items != NULL) {
                    for (auto elem: *this->items->items) {
                        string str = (elem->item_type == function_ || elem->item_type == constStmt_)
                                     ? "/" + ClassTable::moduleClassName : "";

                        if (!str.empty()) {
                            elem->curClassName = this->className + "/" + *this->name + str;
                        }
                        elem->getAllItems(className + "/" + *this->name + str);
                    }
                }
                break;
            case enum_:
                this->classTableItem = ClassTableItem();
                classTableItem.classType = ClassTableItem::enum_;
                this->curClassName = className + "/" + *this->name;
                if (this->visibility == pub) this->classTableItem.isPub = true;
                ClassTable::Instance()->addClass(className + "/" + *this->name, classTableItem);

                if (this->enumItems != NULL) {
                    for (auto elem: *this->enumItems->items) {
                        elem->curClassName = className + "/" + *this->name;
                        elem->getAllItems(className + "/" + *this->name);
                    }
                }

                break;
            case struct_:
                this->classTableItem = ClassTableItem();
                classTableItem.classType = ClassTableItem::struct_;
                if (this->visibility == pub) this->classTableItem.isPub = true;
                ClassTable::Instance()->addClass(className + "/" + *this->name, classTableItem);
                this->curClassName = className + "/" + *this->name;
                if (this->structItems != NULL && this->structItems->items != NULL) {
                    for (auto elem: *this->structItems->items) {
                        elem->curClassName = className + "/" + *this->name;
                        elem->getAllItems(className + "/" + *this->name);
                    }
                }
                break;

            case impl_:
                if (this->impl_type == ImplType::trait) {
                    not_completed.push_back(this);
                    this->directory = className;
                }
                break;
        }
    }
    catch (Exception e) {
        throw e;
    }
}


void EnumItemNode::getAllItems(std::string className) {
    this->fieldTableItem = FieldTableItem();
    this->fieldTableItem.isConst = true;
    if (this->visibility == pub) this->fieldTableItem.isPub = true;

    try {
        ClassTable::Instance()->addField(className, *this->name, fieldTableItem);
    }
    catch (Exception e) {
        throw e;
    }
}

void StructFieldNode::getAllItems(std::string className) {
    this->fieldTableItem = FieldTableItem();
    this->fieldTableItem.isConst = false;
    if (this->visibility == pub) this->fieldTableItem.isPub = true;

    try {
        ClassTable::Instance()->addField(className, *this->name, fieldTableItem);
    }
    catch (Exception e) {
        throw e;
    }
}

/* ------ addImpl ------------------------------------*/

void Node::addImpl(string className, bool isTrait) {

}

void ProgramNode::addImpl(string className, bool isTrait) {

    try {
        if (this->item_list != NULL) {
            for (auto elem: *item_list->items) {
                if (elem->item_type == ItemNode::module_ || elem->item_type == ItemNode::impl_)
                    elem->addImpl(className, false);
            }
        }
    }
    catch (Exception e) {
        throw e;
    }
}


void ItemNode::addImpl(string className, bool isTrait) {

    string implClassName = "";
    string traitClassName = "";
    try {
        switch (this->item_type) {
            case module_:
                if (this->items != NULL) {
                    for (auto elem: *items->items) {
                        if (elem->item_type == impl_ || elem->item_type == module_) {
                            elem->addImpl(className + "/" + *this->name, false);
                        }
                    }
                }
                break;

            case impl_:

                if (this->type->type != TypeNode::path_call_expr_) {
                    throw Exception(Exception::NOT_SUPPORT, "Impl not struct type NOT SUPPORT", this->line);
                }

                this->type->pathCallExpr->transformPathCallExpr(className, ExprNode::undefined, true);
                implClassName = this->type->pathCallExpr->className;
                if (!ClassTable::Instance()->isClassExist(implClassName)) {
                    throw Exception(Exception::NOT_EXIST, "Impl struct " + implClassName + " Not Exist", this->line);
                }

                if (ClassTable::Instance()->getClass(implClassName).classType != ClassTableItem::struct_ &&
                    ClassTable::Instance()->getClass(implClassName).classType != ClassTableItem::enum_) {
                    throw Exception(Exception::UNEXPECTED, implClassName + " not struct or enum in impl", this->line);
                }

                if (this->impl_type == trait) {

                    this->expr->transformPathCallExpr(className, ExprNode::undefined, true);
                    traitClassName = this->expr->className;
                    if (!ClassTable::Instance()->isClassExist(traitClassName)) {
                        throw Exception(Exception::NOT_EXIST, "Trait struct in impl" + traitClassName + "Not Exist",
                                        this->line);
                    }

                    ClassTable::Instance()->addParent(implClassName, traitClassName);
                    ClassTable classTable = *(ClassTable::Instance());
                    this->checkImpl(implClassName, traitClassName);


                }

                if (this->items != NULL) {
                    for (auto elem: *items->items) {
                        if (this->impl_type == trait && elem->visibility == pub) {
                            throw Exception(Exception::PUB_NOT_PERMITTED,
                                            "pub` not permitted here because it's implied :" + implClassName + " " +
                                            *elem->name, this->line);
                        }

                        elem->visibility = pub;
                        elem->curClassName = implClassName;
                        elem->addImpl(implClassName, this->impl_type == trait);
                    }
                }

                if (this->impl_type == trait) {
                    ClassTable::isCorrectChild(implClassName, traitClassName);
                }

                this->className = implClassName;
                this->curClassName = implClassName;


                break;
            case function_:
                this->methodTableItem = MethodTableItem();
                if (this->body != NULL) this->methodTableItem.isHasBody = true;
                if (this->visibility == pub) this->methodTableItem.isPub = true;

                if (ClassTable::Instance()->getClass(className).classType != ClassTableItem::trait_ &&
                    !this->methodTableItem.isHasBody) {
                    throw Exception(Exception::NOT_IMPLEMICATION, *this->name + " NOT_IMPLEMICATION", this->line);
                }

                if (isTrait &&
                    !ClassTable::Instance()->isMethodExist(ClassTable::Instance()->getClass(className).parentName,
                                                           *this->name)) {
                    throw Exception(Exception::NOT_EXIST, "Impl Error: method " + *this->name + " in parent trait " +
                                                          ClassTable::Instance()->getClass(className).parentName,
                                    this->line);
                }

                if (isTrait) {
                    this->methodTableItem.isPub = ClassTable::Instance()->getMethod(
                            ClassTable::Instance()->getClass(className).parentName, *this->name).isPub;
                }

                if ((this->params->func_type == FuncParamListNode::self_ref
                     || this->params->func_type == FuncParamListNode::self)
                    || this->params->func_type == FuncParamListNode::mut_self_ref) {
                    this->methodTableItem.isStatic = false;

                    if (this->params->func_type == FuncParamListNode::self_ref) {
                        this->methodTableItem.isRefSelf = true;
                    }
                }

                this->className = className;
                ClassTable::Instance()->addMethod(className, *this->name, this->methodTableItem);

                break;
            case constStmt_:
                this->fieldTableItem = FieldTableItem();
                if (this->expr != NULL) this->fieldTableItem.isInit = true;
                if (this->visibility == pub) this->fieldTableItem.isPub = true;
                if (!this->fieldTableItem.isInit &&
                    ClassTable::Instance()->getClass(className).classType != ClassTableItem::trait_) {
                    throw Exception(Exception::NOT_IMPLEMICATION, *this->name + " NOT_DEFINED", this->line);
                }

                if (isTrait && !ClassTable::Instance()->
                        isFieldExist(ClassTable::Instance()->getClass(className).parentName, *this->name)) {
                    throw Exception(Exception::NOT_EXIST, "Impl Error: field " + className + " " + *this->name +
                                                          "  not exist in parent trait " +
                                                          ClassTable::Instance()->getClass(className).parentName,
                                    this->line);
                }

                if (isTrait) {
                    this->fieldTableItem.isPub = ClassTable::Instance()->getField(
                            ClassTable::Instance()->getClass(className).parentName, *this->name).isPub;
                }
                fieldTableItem.isConst = true;
                ClassTable::Instance()->addField(className, *this->name, this->fieldTableItem);
                break;

            case struct_:
            case enum_:
            case trait_:
                break;
        }
    }

    catch (Exception e) {
        throw e;
    }
}


DataType TypeNode::convertToDataType(const string &className) {
    DataType dataType = DataType();

    switch (this->type) {

        case emptyType_:
            dataType.type = DataType::undefined_;
            break;
        case int_:
            dataType.type = DataType::int_;
            break;
        case char_:
            dataType.type = DataType::char_;
            break;
        case string_:
            dataType.type = DataType::string_;
            break;
        case float_:
            dataType.type = DataType::float_;
            break;
        case bool_:
            dataType.type = DataType::bool_;
            break;
        case id_:
            dataType.type = DataType::class_;
            break;
        case array_:
            dataType.type = DataType::array_;
            {
                DataType innerDataType = this->typeArr->convertToDataType(className);
                this->exprArr->transform();
                dataType.arrType = innerDataType.arrType;

                if (exprArr->type != ExprNode::int_lit) {
                    throw Exception(Exception::INCORRECT_CONST, "not INT_LIT", this->line);
                }

                if (this->exprArr->Int <= 0) {
                    throw Exception(Exception::INCORRECT_ARR_LENGTH, "array length less than one", this->line);
                }

                if (innerDataType.type == DataType::array_) {
                    dataType.arrLength = innerDataType.arrLength;
                    dataType.arrLength.push_back(this->exprArr->Int);
                    dataType.arrDeep = innerDataType.arrDeep + 1;
                    dataType.arrType = innerDataType.arrType;
                } else {
                    dataType.arrLength.push_back(this->exprArr->Int);
                    dataType.arrDeep = 1;
                    dataType.arrType = innerDataType.type;
                    dataType.id = innerDataType.id;
                }
            }

            break;
        case path_call_expr_:
            dataType.type = DataType::class_;
            this->pathCallExpr->transformPathCallExpr(className, ExprNode::undefined, true);
            dataType.id = this->pathCallExpr->className;

            if (ClassTable::Instance()->getClass(dataType.id).classType == ClassTableItem::mod_) {
                throw Exception(Exception::UNEXPECTED, dataType.id + "is module and not a type", this->line);
            }
            break;
    }

    return dataType;
}

void Node::addDataTypeToDeclaration(const string &className) {

}

void ItemNode::addDataTypeToDeclaration(const string &className) {

    set<int> enumSt;
    switch (this->item_type) {

        case enum_:

            for (auto elem: *this->enumItems->items) {
                elem->addDataTypeToDeclaration(className + "/" + *this->name, enumSt);
            }
            this->curClassName = className + "/" + *this->name;


            break;
        case function_:
            this->methodTableItem.returnDataType = this->returnType->convertToDataType(className);
            if (this->methodTableItem.returnDataType.type == DataType::undefined_) {
                this->methodTableItem.returnDataType.type = DataType::void_;
            }


            if (this->params != NULL) {

                if (this->params->func_type == FuncParamListNode::self) {
                    VarTableItem varItem = VarTableItem(VarTable::SELF_PARAM, DataType::StructDataType(curClassName),
                                                        false, false, true, false, body);

                    this->methodTableItem.paramTable.items.push_back(varItem);
                }

                if (this->params->func_type == FuncParamListNode::self_ref) {
                    VarTableItem varItem = VarTableItem(VarTable::SELF_PARAM, DataType::StructDataType(curClassName),
                                                        false, true, true, false, body);

                    this->methodTableItem.paramTable.items.push_back(varItem);
                }

                if (this->params->func_type == FuncParamListNode::mut_self_ref) {
                    VarTableItem varItem = VarTableItem(VarTable::SELF_PARAM, DataType::StructDataType(curClassName),
                                                        true, true, true, false, body);

                    this->methodTableItem.paramTable.items.push_back(varItem);
                }

                for (auto elem: *this->params->items) {
                    elem->methodName = *this->name;
                    elem->addDataTypeToDeclaration(className);
                    elem->varTableItem.blockExpr = this->body;

                    if (this->methodTableItem.paramTable.isExist(*elem->name)) {
                        throw Exception(Exception::DEFINED_MULTIPLE,
                                        "Function Param " + *elem->name + " in function " + *this->name +
                                        " DEFINED_MULTIPLE", elem->line);
                    }
                    this->methodTableItem.paramTable.items.push_back(elem->varTableItem);

                }
            }
            this->methodTableItem.body = this->body;
            ClassTable::Instance()->updateMethod(className, *this->name, this->methodTableItem);
            break;
        case constStmt_:
            this->fieldTableItem.dataType = this->type->convertToDataType(className);
            this->expr->transformConst();
            this->fieldTableItem.value = this->expr;

            if (!fieldTableItem.dataType.isEquals(this->expr->dataType)) {
                throw Exception(Exception::INCORRECT_TYPE,
                                "Expected type for " + *this->name + " in " + className + ":" +
                                fieldTableItem.dataType.toString() + " Result: " + this->expr->dataType.toString(),
                                this->line);
            }

            ClassTable::Instance()->updateField(className, *this->name, this->fieldTableItem);
            break;
        case struct_:
            if (this->structItems != NULL) {
                for (auto elem: *this->structItems->items) {
                    elem->addDataTypeToDeclaration(className + "/" + *this->name);
                }
            }

            this->curClassName = className + "/" + *this->name;
            break;
        case impl_:

            for (auto elem: *this->items->items) {
                elem->addDataTypeToDeclaration(this->className);
            }
            break;
        case module_:
            this->curClassName = className + "/" + *this->name + "/" + ClassTable::moduleClassName;
            if (this->items != NULL) {
                for (auto elem: *this->items->items) {
                    string str = (elem->item_type == function_ || elem->item_type == constStmt_)
                                 ? "/" + ClassTable::moduleClassName : "";

                    if (elem->item_type == function_ || elem->item_type == constStmt_) {
                        elem->curClassName = this->curClassName;
                    }
                    elem->addDataTypeToDeclaration(className + "/" + *this->name + str);
                }
            }

            break;
        case trait_:
            this->curClassName = className + "/" + *this->name;
            if (this->items != NULL) {
                for (auto elem: *this->items->items) {
                    elem->addDataTypeToDeclaration(className + "/" + *this->name);
                }
            }
            break;
    }
}


void EnumItemNode::addDataTypeToDeclaration(const string &className, set<int> &st) {
    if (this->expr == NULL && st.empty()) {
        this->expr = ExprNode::ExprFromIntLiteral(ExprNode::int_lit, 0);
    }

    if (this->expr == NULL) {
        this->expr = ExprNode::ExprFromIntLiteral(ExprNode::int_lit, *st.rbegin() + 1);
    }

    if (this->expr != NULL) {
        this->expr->transformConst();

        if (this->expr->type != ExprNode::int_lit) {
            throw Exception(Exception::NOT_CONST, "ENUM VALUE SHOULD BE INT LITERAL", this->line);
        }
    }

    if (this->expr->Int > 255 || this->expr->Int < 0) {
        throw Exception(Exception::INCORRECT_ENUM_VALUE, "ENUM VALUE SHOULD BE u8", this->line);
    }

    if (st.count(this->expr->Int)) {
        throw Exception(Exception::INCORRECT_ENUM_VALUE,
                        "INCORRECT_ENUM_VALUE: ENUM VALUE " + to_string(this->expr->Int) +
                        " occurs twice in " +
                        className, this->line);
    }


    this->dataType = DataType(DataType::int_);

    st.insert(this->expr->Int);
    this->fieldTableItem.dataType = DataType::int_;
    this->fieldTableItem.value = this->expr;
    ClassTable::Instance()->updateField(className, *this->name, this->fieldTableItem);
}


void StructFieldNode::addDataTypeToDeclaration(const string &className) {
    this->fieldTableItem.dataType = this->type->convertToDataType(className);
    this->dataType = this->fieldTableItem.dataType;
    ClassTable::Instance()->updateField(className, *this->name, fieldTableItem);
}

void FuncParamNode::addDataTypeToDeclaration(const string &className) {
    this->varTableItem = VarTableItem();
    this->varTableItem.id = *this->name;
    this->varTableItem.dataType = this->type->convertToDataType(className);

    bool isTrait = false;

    if (this->varTableItem.dataType.isClass()) {
        ClassTableItem classTableItem = ClassTable::Instance()->getClass(this->varTableItem.dataType.id);

        if (classTableItem.classType == ClassTableItem::mod_) {
            throw Exception(Exception::TYPE_ERROR,
                            this->varTableItem.dataType.id + "cannot be function param because it`s mod_", this->line);
        }

        isTrait = classTableItem.classType == ClassTableItem::trait_;
    }

    if (this->varTableItem.dataType.isClass()) {
        string className = this->varTableItem.dataType.id;
        if (ClassTable::isEnum(className)) {
            this->varTableItem.dataType = DataType(DataType::int_);
        }
    }

    if (this->type->isImpl && !isTrait) {
        throw Exception(Exception::TYPE_ERROR,
                        "keyword  `impl` can`t use with " + this->varTableItem.dataType.toString() +
                        " because it`s not a trait_", this->line);
    } else if (isTrait && !this->type->isImpl) {
        throw Exception(Exception::TYPE_ERROR,
                        this->varTableItem.dataType.toString() +
                        " can`t be a function param because it`s trait_", this->line);
    }

    this->convertEnumValue();

    switch (this->param_type) {

        case noMut:
            break;
        case mut:
            this->varTableItem.isMut = true;
            break;
        case mut_ref:
            this->varTableItem.isMut = true;
            this->varTableItem.isRef = true;
            break;
        case link:
            this->varTableItem.isRef = true;
            break;
    }
}

void ExprNode::transformPathCallExpr(string className, ExprNode::Type type, bool isType) {
    ExprNode *cur = this;
    vector<string> namePath;

    while (cur != NULL && cur->type == ExprNode::path_call_expr) {
        namePath.push_back(*cur->Name);
        cur = cur->expr_left;
    }

    reverse(all(namePath));
    ///TODO доделать


    if (isType == false && namePath.size() == 0) {
        this->className = className;
        if (type == ExprNode::static_method) {
            this->methodName = *this->Name;
        } else {
            this->fieldName = *this->Name;
        }
        return;
    }

    if (type == ExprNode::static_method) {
        this->methodName = namePath.back();
        namePath.pop_back();
    } else if (isType == false) {
        this->fieldName = namePath.back();
        namePath.pop_back();
    }

    string res = "";
    switch (cur->type) {
        case ExprNode::id_:

            if (ClassTable::Instance()->isClassExist(className)) {
                res += ClassTable::getDirectory(className);
            } else {
                res += className;
            }
            res += +"/" + *cur->Name;

            break;
        case ExprNode::self_expr:
            ///TODO доделать

            /// пока реализовать случай вызова статика
            if (cur != this) {
                res = className;

                if (ClassTable::Instance()->isClassExist(className)) {
                    res = ClassTable::getDirectory(className);
                }
            } else {
                res = className;
            }

            break;
        case ExprNode::super_expr:
            /// TODO доделать

            /// пока реализовать случай вызова статика
            if (cur != this) {
                if (ClassTable::Instance()->isClassExist(className)) {
                    res = ClassTable::getDirectory(className);
                }
                res = ClassTable::getDirectory(res);
            } else {
                res = ClassTable::Instance()->getClass(className).parentName;
            }
            break;
        case ExprNode::crate_expr:
            res = ClassTable::globalClassName;
            break;
        default:
            break;
    }

    for (auto elem: namePath) {
        res += "/" + elem;
    }

    if (!ClassTable::Instance()->isClassExist(res)) {
        res += "/" + ClassTable::moduleClassName;
    }

    if (!ClassTable::Instance()->isClassExist(res)) {
        throw Exception(Exception::NOT_EXIST, res + " NOT_EXIST", this->line);
    }

    this->className = res;

}

bool ExprNode::isLiteral() {
    return this->type == ExprNode::int_lit || this->type == ExprNode::bool_lit ||
           this->type == ExprNode::char_lit || this->type == ExprNode::float_lit ||
           this->type == ExprNode::string_lit || this->type == ExprNode::raw_string_lit;
}

bool ExprNode::isSimpleType() {
    return this->dataType.isInt() || this->dataType.isFloat() || this->dataType.isChar() || this->dataType.isBool();
}

void ProgramNode::transform(bool isConvertedToConst) {

    string tmp = ClassTable::globalClassName + "/" + ClassTable::moduleClassName;
    this->curClassName = tmp;
//    ClassTable::addClassToConstTable(tmp, tmp);
    if (this->item_list != NULL) {
        for (auto item: *this->item_list->items) {
            try {
                if (item->item_type == ItemNode::function_ || item->item_type == ItemNode::constStmt_) {
                    item->curClassName = this->curClassName;
                }
                item->transform(isConvertedToConst);

            }
            catch (Exception e) {
                cerr << e.getMessage() << endl;
            }
        }
    }

}

void ProgramNode::makeAllConversions() {
    RTLContainer();
    this->getAllItems(ClassTable::globalClassName);
    this->transform(true);
}

void ItemNode::transform(bool isConvertedToConst) {

    try {
        switch (this->item_type) {

            case function_: {
                returnTypes.clear();
                if (body != NULL) {

                    body->curClassName = curClassName;
                    body->curMethodName = *this->name;
                }

                if (*this->name == "selfFunc") {
                    "ffff";
                }

                if (ClassTable::Instance()->isMethodExist(ConstTable::RTLClassName, *this->name)) {
                    throw Exception(Exception::NOT_SUPPORT,
                                    *this->name + " funtion is reserved by RTL", this->line);
                }

                vector<DataType> paramTypes;
                for (auto elem: ClassTable::Instance()->getMethod(curClassName, *this->name).paramTable.items) {
                    elem.blockExpr = body;
                    paramTypes.push_back(elem.dataType);

                    if (elem.isRef && elem.dataType.isSimple()) {
                        throw Exception(Exception::NOT_SUPPORT,
                                        elem.dataType.toString() + " is simple and ref. Not support this", this->line);
                    }

                    ClassTable::Instance()->addLocalParam(curClassName, *this->name, elem);
                }

                if (ClassTable::Instance()->getMethod(curClassName, *this->name).isStatic == false &&
                    paramTypes.size()) {
                    paramTypes.erase(paramTypes.begin());
                }

                if (*this->name == "main") {
                    int x = 10 + 10;
                }

                blockExprList.push_back(body);
                if (this->body != NULL) {
                    this->body->transform(isConvertedToConst);
                    MethodTableItem methodTableItem = ClassTable::Instance()->getMethod(this->curClassName,
                                                                                        *this->name);
                    if (!this->body->dataType.isEquals(methodTableItem.returnDataType)) {
                        throw Exception(Exception::TYPE_ERROR,
                                        *this->name + " should return " +
                                        methodTableItem.returnDataType.toString() +
                                        " but result: " + body->dataType.toString(), this->line);
                    }

                    returnTypes.push_back(methodTableItem.returnDataType);
                    if (!DataType::isEquals(returnTypes)) {
                        throw Exception(Exception::TYPE_ERROR,
                                        *this->name + " should return  " +
                                        methodTableItem.returnDataType.toString() +
                                        " but result is not", this->line);
                    }
                }

                returnTypes.clear();
                blockExprList.pop_back();
                if (blockExprList.size()) {
                    throw Exception(Exception::UNEXPECTED, "blockexpr не удалил(", this->line);
                }

                for (auto param: *this->params->items) {
                    try {
                        if (param->dataType.isClass()) {
                            if (!ClassTable::isHaveAccess(curClassName, param->dataType.id)) {
                                throw Exception(Exception::ACCESS_ERROR,
                                                *this->name + " has not access to " + param->dataType.id, this->line);
                            }

                            bool isPub = ClassTable::Instance()->getMethod(curClassName, *this->name).isPub;
                            if (isPub && !ClassTable::Instance()->getClass(param->dataType.id).isPub) {
                                throw Exception(Exception::PRIVATE_ERROR,
                                                *this->name + " has param  " + param->dataType.id + " is private",
                                                this->line);
                            }
                        }
                    }
                    catch (Exception e) {
                        throw e;
                    }
                }

                if (this->dataType.isClass()) {

                    if (!ClassTable::isHaveAccess(curClassName, dataType.id)) {
                        throw Exception(Exception::ACCESS_ERROR, *this->name + " has not access to " + dataType.id,
                                        this->line);
                    }

                }
            }
                break;
            case constStmt_:
                if (this->expr != NULL) {
                    this->expr->curClassName = curClassName;
                    // this->expr->curMethodName = curMethodName;
                    this->expr->transform(isConvertedToConst);
                }

                if (this->dataType.isClass()) {
                    if (ClassTable::isHaveAccess(curClassName, dataType.id)) {
                        throw Exception(Exception::ACCESS_ERROR, *this->name + " has not access to " + dataType.id,
                                        this->line);
                    }

                    if (!ClassTable::Instance()->getClass(dataType.id).isPub) {
                        throw Exception(Exception::PRIVATE_ERROR,
                                        *this->name + " is public but type " + dataType.id + " is private", this->line);
                    }
                }


//                ClassTable::addFieldRefToConstTable(curClassName, curClassName, *this->name,
//                                                    ClassTable::Instance()->getField(curClassName,
//                                                                                     *this->name).dataType);
                break;
            case trait_:
            case impl_:
            case module_:
                if (items != NULL) {
                    for (auto elem: *this->items->items) {
                        if (item_type == impl_ && impl_type == ImplType::inherent) {
                            elem->isEqualDataType(elem);
                        }
                        elem->transform(isConvertedToConst);
                    }
                }
                break;
            case struct_: {
                vector<DataType> params;

                if (this->structItems == NULL) {
                    return;
                }
                for (auto elem: *structItems->items) {
                    if (elem->dataType.isClass()) {

                        if (!ClassTable::isHaveAccess(curClassName, dataType.id)) {
                            throw Exception(Exception::ACCESS_ERROR, *this->name + " has not access to " + dataType.id,
                                            this->line);
                        }

                        bool isPubField = ClassTable::Instance()->getField(curClassName, *elem->name).isPub;
                        bool isPrivateType = !ClassTable::Instance()->getClass(elem->dataType.id).isPub;
                        if (isPubField && isPrivateType) {
                            throw Exception(Exception::PRIVATE_ERROR,
                                            *elem->name + " is public but type " + elem->dataType.id + " is private",
                                            elem->line);
                        }
                    }

                    params.push_back(elem->dataType);
//                    ClassTable::addFieldRefToConstTable(curClassName, curClassName, *elem->name, elem->dataType);

                }

//                ClassTable::addMethodRefToConstTable(curClassName, curClassName, ConstTable::init, vector<DataType>(),
//                                                     DataType(DataType::void_));

//                ClassTable::addMethodRefToConstTable(curClassName, curClassName, ConstTable::clinit, vector<DataType>(),
//                                                     DataType(DataType::void_));

                break;
            }
            case enum_:

                for (auto elem: *this->enumItems->items) {
                    //  ClassTable::addFieldRefToConstTable(curClassName, curClassName, *elem->name, elem->dataType);
                    elem->expr->transform();
                }

                break;
        }
    }
    catch (Exception e) {
        blockExprList.clear();
        cerr << e.getMessage() << endl;
    }
}

bool ItemNode::isHaveParent() {
    return this->parentName != NULL;
}

void ItemNode::checkImpl(const string &structName, const string &traitName) {

    string tmpTraitName = traitName;

    while (ClassTable::isHaveParent(tmpTraitName)) {
        tmpTraitName = ClassTable::getParentClassName(tmpTraitName);
        if (!impl_set[structName].count(tmpTraitName)
            && ClassTable::Instance()->getClass(tmpTraitName).isHaveAbstract()) {
            throw Exception(Exception::NOT_IMPLEMICATION, structName + " should have impl " + tmpTraitName, this->line);
        }
    }
}

void ItemNode::modifyInheritence() {
    switch (item_type) {
        case trait_:
            if (this->isHaveParent()) {
                ClassTable::Instance()->addParent(this->directory + "/" + *this->name,
                                                  this->directory + "/" + *this->parentName);
            }
            break;
        case impl_:
            if (this->type->type == TypeNode::path_call_expr_) {
                this->type->pathCallExpr->transformPathCallExpr(directory, ExprNode::undefined, true);
                this->expr->transformPathCallExpr(directory, ExprNode::undefined, true);
                string parentName = this->expr->className;
                string name = this->type->pathCallExpr->className;
                impl_set[name].insert(parentName);
            }
            break;
    }
}

void StmtListNode::transform(bool isConvertedToConst) {

    if (this->stmts != NULL) {
        for (auto elem: *this->stmts) {
            elem->curClassName = curClassName;
            elem->curMethodName = curMethodName;
            elem->transform(isConvertedToConst);
        }
    }
}

void StmtNode::transform(bool isConvertedToConst) {

    auto classTable = ClassTable::Instance();

    try {

        if (this->expr != NULL && this->expr->type == ExprNode::struct_creation) {
            this->expr->transformStructExpr();
            if (this->expr->expr_middle != NULL) {
                auto expression = this->expr->expr_middle;
                this->expr->expr_middle = NULL;
                this->expr = expression;
            }
        }

        switch (this->type) {
            case exprstmt:
                this->expr->curClassName = curClassName;
                this->expr->curMethodName = curMethodName;
                this->expr->transform(isConvertedToConst);
                break;
            case let:
                this->varTableItem = VarTableItem();
                if (this->let_type == mut) {
                    this->varTableItem.isMut = mut;
                }
                varTableItem.id = *this->name;
                varTableItem.blockExpr = blockExprList.back();
                {
                    DataType arrDataType = DataType();

                    if (this->typeChild == NULL || this->typeChild->type == TypeNode::array_) {
                        arrDataType = this->typeChild->convertToDataType(curClassName).getArrDataType();
                    }

                    if (this->expr != NULL) {
                        this->expr->curClassName = curClassName;
                        this->expr->curMethodName = curMethodName;
                        this->expr->arrDataType = arrDataType;
                        this->expr->transform(isConvertedToConst);
                    }

                    if (this->typeChild == NULL || this->typeChild->type == TypeNode::emptyType_) {
                        varTableItem.dataType = expr->dataType;
                    } else {
                        varTableItem.dataType = this->typeChild->convertToDataType(curClassName);

                        if (!isEqualDataType(this->expr->dataType, varTableItem.dataType)) {
                            throw Exception(Exception::INCORRECT_TYPE,
                                            "incorrect let " + varTableItem.id + " datatype. Expected: " +
                                            varTableItem.dataType.toString() +
                                            " result: " + this->expr->dataType.toString(), this->line);
                        }
                    }
                }

                this->convertEnumValue();
                ClassTable::Instance()->addLocalParam(curClassName, curMethodName, this->varTableItem);
                this->localVarNum = Node::getVarNumber(blockExprList.back(), curClassName, curMethodName, *this->name);
                break;
            case const_:
                this->varTableItem = VarTableItem();

                varTableItem.isConst = true;
                varTableItem.id = *this->name;

                if (this->expr == NULL) {
                    throw Exception(Exception::UNEXPECTED, "const " + *this->name + " must be initialized", this->line);
                }

                this->expr->curClassName = curClassName;
                this->expr->curMethodName = curMethodName;
                this->expr->transformConst();
                this->expr->transform();
                varTableItem.dataType = this->typeChild->convertToDataType(curClassName);

                if (!isEqualDataType(this->expr->dataType, varTableItem.dataType)) {
                    throw Exception(Exception::INCORRECT_TYPE, "incorrect datatype", this->line);
                }

                varTableItem.blockExpr = blockExprList.back();
                this->convertEnumValue();
                ClassTable::Instance()->addLocalParam(curClassName, curMethodName, this->varTableItem);
                this->localVarNum = Node::getVarNumber(blockExprList.back(), curClassName, curMethodName, *this->name);
                break;
            case semicolon:
            case expression:
                break;
        }
    }
    catch (Exception e) {
        cerr << e.getMessage() << "\n";
    }
}

void ExprNode::transform(bool isConvertedToConst) {

    auto classTable = ClassTable::Instance();
    if (this->expr_left != NULL) {
        this->expr_left->transformStructExpr();
        if (this->expr_left->expr_middle != NULL) {
            auto expr = this->expr_left->expr_middle;
            this->expr_left->expr_middle = NULL;
            this->expr_left = expr;
        }
    }

    if (this->expr_right != NULL) {
        this->expr_right->transformStructExpr();
        if (this->expr_right->expr_middle != NULL) {
            auto expr = this->expr_right->expr_middle;
            this->expr_right->expr_middle = NULL;
            this->expr_right = expr;
        }
    }

    switch (this->type) {

        case plus:
        case minus:
        case mul_expr:
        case div_expr:

            addMetaInfo(this->expr_left);
            addMetaInfo(this->expr_right);
            checkCancelExprNode(this->expr_left);
            checkCancelExprNode(this->expr_right);

            this->expr_left->transform(isConvertedToConst);
            this->expr_right->transform(isConvertedToConst);

            if (this->expr_left->isLiteral() && this->expr_right->isLiteral() && isConvertedToConst) {
                this->transformConst();
                this->transform();
            } else {
                if (!this->expr_left->dataType.isEquals(expr_right->dataType)) {
                    throw Exception(Exception::NOT_EQUAL_DATA_TYPE,
                                    "NOT EQUAL DATA_TYPE " + this->expr_left->dataType.toString() + " " +
                                    this->expr_right->dataType.toString(), this->line);
                }

                if (this->expr_left->dataType.type != DataType::int_
                    && this->expr_left->dataType.type != DataType::float_) {
                    throw Exception(Exception::OPERATION_NOT_SUPPORTED,
                                    "datatype " + this->expr_left->dataType.toString() +
                                    " not supported maths operation", this->line);
                }

                this->dataType = this->expr_left->dataType;
            }
            break;
        case mod:

            addMetaInfo(this->expr_left);
            addMetaInfo(this->expr_right);
            checkCancelExprNode(this->expr_left);
            checkCancelExprNode(this->expr_right);

            this->expr_left->transform(isConvertedToConst);
            this->expr_right->transform(isConvertedToConst);

            if (!this->expr_left->dataType.isEquals(expr_right->dataType)) {
                throw Exception(Exception::NOT_EQUAL_DATA_TYPE,
                                "NOT EQUAL DATA_TYPE" + this->expr_left->dataType.toString() + " " +
                                this->expr_right->dataType.toString());
            }

            if (!this->expr_left->dataType.isInt() && !this->expr_left->dataType.isFloat()) {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED,
                                "datatype " + this->expr_left->dataType.toString() +
                                " not supported operation mod", this->line);
            }

            this->dataType = this->expr_left->dataType;

            if (this->expr_left->isLiteral() && this->expr_right->isLiteral() && isConvertedToConst) {
                this->transformConst();
                this->transform();
            }

            break;

        case equal:
        case not_equal:
        case greater:
        case less:
        case greater_equal:
        case less_equal:

            addMetaInfo(this->expr_left);
            addMetaInfo(this->expr_right);
            checkCancelExprNode(this->expr_left);
            checkCancelExprNode(this->expr_right);

            this->expr_left->transform(isConvertedToConst);
            this->expr_right->transform(isConvertedToConst);


            if (!this->expr_left->dataType.isEquals(expr_right->dataType)) {
                throw Exception(Exception::NOT_EQUAL_DATA_TYPE,
                                "NOT EQUAL DATA_TYPE " + this->expr_left->dataType.toString() + " " +
                                this->expr_right->dataType.toString(), this->line);
            }

            if (this->expr_left->dataType.type == DataType::array_
                || this->expr_left->dataType.type == DataType::class_) {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED,
                                "datatype " + this->expr_left->dataType.toString() +
                                " not supported comparison operation", this->line);
            }

            this->dataType = DataType(DataType::bool_);

            if (this->expr_left->isLiteral() && this->expr_right->isLiteral() && isConvertedToConst) {
                this->transformConst();
                this->transform();
            }

            break;

        case uminus:
            addMetaInfo(this->expr_left);
            checkCancelExprNode(this->expr_left);
            this->expr_left->transform(isConvertedToConst);
            //  this->expr_right->curMethodName = curMethodName;

            if (this->expr_left->dataType.type != DataType::float_
                && this->expr_left->dataType.type != DataType::int_) {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED,
                                "datatype " + this->expr_left->dataType.toString() +
                                " not supported uminus operation", this->line);
            }
            this->dataType = this->expr_left->dataType;

            if (this->expr_left->isLiteral()) {
                this->transformConst();
                this->transform();
            }

            break;

        case negotation:

            addMetaInfo(this->expr_left);
            checkCancelExprNode(this->expr_left);
            this->expr_left->transform(isConvertedToConst);

            //   this->expr_right->curMethodName = curMethodName;

            if (this->expr_left->dataType.type != DataType::bool_) {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED,
                                "datatype " + this->expr_left->dataType.toString() +
                                " not supported uminus operation", this->line);
            }
            this->dataType = this->expr_left->dataType;

            if (this->expr_left->isLiteral()) {
                this->transformConst();
                this->transform();
            }

            break;

        case or_:
        case and_:
            addMetaInfo(this->expr_left);
            addMetaInfo(this->expr_right);
            checkCancelExprNode(this->expr_left);
            checkCancelExprNode(this->expr_right);

            this->expr_left->transform(isConvertedToConst);
            this->expr_right->transform(isConvertedToConst && false);

            if (this->expr_left->isLiteral() && this->expr_right->isLiteral() && isConvertedToConst) {
                this->transformConst();
                this->transform();
            }

            if (!this->expr_left->dataType.isEquals(expr_right->dataType)) {
                throw Exception(Exception::NOT_EQUAL_DATA_TYPE,
                                "NOT EQUAL DATA_TYPE " + this->expr_left->dataType.toString() + " " +
                                this->expr_right->dataType.toString(), this->line);
            }

            if (this->expr_left->dataType.type != DataType::bool_) {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED,
                                "datatype " + this->expr_left->dataType.toString() +
                                " not supported and/or operation", this->line);
            }

            this->dataType = this->expr_left->dataType;

            break;
        case asign:

            addMetaInfo(this->expr_left);
            addMetaInfo(this->expr_right);
            checkCancelExprNode(this->expr_left);
            checkCancelExprNode(this->expr_right);

            this->expr_left->transform(isConvertedToConst);
            this->expr_right->transform(isConvertedToConst);


            if (!this->expr_left->isVar()) {
                throw Exception(Exception::NOT_A_VAR, "left operand not a var", this->line);
            }
            {
                bool isClass = this->expr_left->dataType.isClass() && this->expr_right->dataType.isClass();
                bool isParent = isClass && ClassTable::Instance()->isParent(this->expr_right->dataType.id,
                                                                            this->expr_left->dataType.id);
                if (!this->expr_left->dataType.isEquals(expr_right->dataType) && !isParent) {
                    throw Exception(Exception::NOT_EQUAL_DATA_TYPE,
                                    "NOT EQUAL DATA_TYPE in asign: " + this->expr_left->dataType.toString() +
                                    " and " +
                                    this->expr_right->dataType.toString(), this->line);
                }
            }

            //TODO добавить обработку констант
            if (this->expr_left->localVarNum != -1) { ///
                VarTableItem varTableItem = ClassTable::Instance()->getLocalVar(curClassName, curMethodName,
                                                                                this->expr_left->localVarNum);
                if (this->expr_left->isConst || this->expr_left->isMut == false) {
                    throw Exception(Exception::OPERATION_NOT_SUPPORTED,
                                    varTableItem.id + "is const and can`t supported asign operation", this->line);
                }
            } else if (!this->expr_left->fieldName.empty()) {
                FieldTableItem fieldTableItem = ClassTable::Instance()->getField(curClassName,
                                                                                 this->expr_left->fieldName);
                if (this->expr_left->isConst || this->expr_left->isMut == false) {
                    throw Exception(Exception::OPERATION_NOT_SUPPORTED,
                                    this->expr_left->fieldName + "is const and can`t supported asign operation",
                                    this->line);
                }
            }

            if (this->expr_left->isConst || this->expr_left->isMut == false) {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED,
                                *this->expr_left->Name + " is const and can`t supported asign operation", this->line);
            }

            this->dataType = DataType(DataType::void_);
            /// TODO добавить обработку для массива

            if (this->expr_left->type == index_expr) {
                this->type = arr_asign;
                this->expr_middle = this->expr_left->expr_right;
                this->expr_left->expr_right = NULL;
                this->expr_left = this->expr_left->expr_left;
            } else if (this->expr_left->type == field_access_expr) {
                this->type = point_assign;
                this->expr_middle = ExprNode::PathCallExpr(id_, this->expr_left->Name, NULL);
                this->expr_left->expr_right = NULL;
                this->expr_left = this->expr_left->expr_left;
            }


            break;
        case array_expr:

            if (this->expr_list != NULL) {
                for (auto elem: *expr_list->exprs) {
                    addMetaInfo(elem);
                    checkCancelExprNode(elem);
                    elem->transform(isConvertedToConst);
                }

                if (this->expr_list->exprs->size()) {

                    vector<DataType> arrTypes;
                    DataType firstElement = this->expr_list->exprs->front()->dataType;
                    if (firstElement.type != DataType::array_) {
                        for (auto elem: *this->expr_list->exprs) {
                            auto dataType = elem->dataType;

                            if (dataType.type != DataType::class_) {
                                if (!dataType.isEquals(firstElement)) {
                                    throw Exception(Exception::TYPE_ERROR,
                                                    "not correct types in array", elem->line);
                                }
                            } else if (dataType.type == DataType::class_) {
                                if (!dataType.isEquals(firstElement)
                                    && (this->arrDataType.type != DataType::class_ ||
                                        !ClassTable::Instance()->isParent(dataType.id, this->arrDataType.id))) {
                                    throw Exception(Exception::TYPE_ERROR,
                                                    "not correct types in array. Expected: " + this->arrDataType.id +
                                                    " Result: " + dataType.id, this->line);
                                }
                            }


                        }


                        this->dataType = DataType();
                        this->dataType.type = DataType::array_;
                        this->dataType.arrDeep = 1;

                        if (firstElement.type != DataType::class_ || arrDataType.isUndefined()) {
                            this->dataType.addArrType(firstElement);
                        } else if (arrDataType.type != DataType::class_) {
                            throw Exception(Exception::TYPE_ERROR,
                                            "type error in array. Expected: " + arrDataType.toString() +
                                            "Result: " +
                                            firstElement.toString(), this->line);
                        } else if (firstElement.isEquals(this->arrDataType)) {
                            this->dataType.addArrType(firstElement);
                        } else if (ClassTable::Instance()->isParent(firstElement.id, this->arrDataType.id)) {
                            this->dataType.addArrType(arrDataType);
                        } else {
                            throw Exception(Exception::TYPE_ERROR,
                                            "type error in array. Expected: " + arrDataType.toString() +
                                            "Result: " +
                                            firstElement.toString(), this->line);
                        }

                    } else {

                        for (auto elem: *this->expr_list->exprs) {
                            if (!elem->dataType.isEquals(firstElement)) {
                                throw Exception(Exception::ARRAY_SIZE, "incorrect size inner arrays", elem->line);
                            }
                            //TODO склеить два массива
                            arrTypes.insert(arrTypes.end(), all(elem->dataType.arrTypes));
                        }
                        this->dataType = firstElement;
                        this->dataType.arrDeep++;
                    }

                    this->dataType.arrLength.push_back(expr_list->exprs->size());
                    this->dataType.arrTypes = arrTypes;

                }
            }
            //TODO тут не забыть нафигачить провер очки
            break;

        case array_expr_auto_fill:

            addMetaInfo(this->expr_left);
            addMetaInfo(this->expr_right);
            checkCancelExprNode(this->expr_left);
            checkCancelExprNode(this->expr_right);

            this->expr_left->transform(isConvertedToConst);
            this->expr_right->transform(isConvertedToConst);

            if (this->expr_right->dataType.type != DataType::int_) {
                throw Exception(Exception::NOT_SUPPORT,
                                "array size expected i32, found " + this->expr_right->dataType.toString(), this->line);
            }

            if (this->expr_left->type != int_lit) {
                if (this->expr_right->isConst == false) {
                    throw Exception(Exception::NOT_CONST, "array size must be constant", this->line);
                }

            }

            if (this->expr_right == NULL) {
                throw Exception(Exception::UNEXPECTED, "expr right is NULL. FUCK YEE", this->line);
            }

            {
                int array_size = this->expr_right->Int;

                for (int i = 0; i < array_size; i++) {
                    if (this->expr_list == NULL) {
                        this->expr_list = new ExprListNode(this->expr_left);
                    } else {
                        ExprListNode::Append(this->expr_list,
                                             this->expr_left); //TODO создание копии элемента а не сам элемент пихать
                    }
                }

                this->expr_left = NULL;
                this->expr_right = NULL;
                this->type = ExprNode::array_expr;
                this->transform(isConvertedToConst);
            }

            break;
        case index_expr:
            addMetaInfo(this->expr_left);
            addMetaInfo(this->expr_right);
            checkCancelExprNode(this->expr_left);
            checkCancelExprNode(this->expr_right);
            this->expr_left->transform(isConvertedToConst);
            this->expr_right->transform(isConvertedToConst);

            if (this->expr_right->dataType.type != DataType::int_) {
                throw Exception(Exception::TYPE_ERROR,
                                "index must be i32. Index type: " + this->expr_right->dataType.toString(), this->line);
            }


            if (this->expr_left->dataType.type != DataType::array_) {
                throw Exception(Exception::TYPE_ERROR,
                                "type error: expected: array_ result: " +
                                this->expr_left->dataType.toString(), this->line);
            }

            {
                DataType newDataType = this->expr_left->dataType;
                newDataType.arrDeep--;
                newDataType.arrLength.pop_back();

                if (newDataType.arrDeep == 0) {
                    newDataType.type = this->expr_left->dataType.arrType;
                }

                this->dataType = newDataType;
                this->isConst = this->expr_left->isConst;
                this->isMut = this->expr_left->isMut;
            }

            this->localVarNum = expr_left->localVarNum;
            this->fieldName = expr_left->fieldName;


            break;
        case range_expr:
            addMetaInfo(this->expr_left);
            addMetaInfo(this->expr_right);
            checkCancelExprNode(this->expr_left);
            checkCancelExprNode(this->expr_right);

            this->expr_left->transform(isConvertedToConst);
            this->expr_right->transform(isConvertedToConst);
            if (!this->expr_left->dataType.isEquals(this->expr_right->dataType)
                || this->expr_left->dataType.type != DataType::int_) {
                throw Exception(Exception::TYPE_ERROR,
                                "range expression must be int_ and result: left=" +
                                expr_left->dataType.toString() +
                                "right=" + expr_right->dataType.toString(), this->line);
            }

            break;
        case field_access_expr: /// Expression.ID
            addMetaInfo(this->expr_left);
            checkCancelExprNode(this->expr_left);
            this->expr_left->transform(isConvertedToConst);

            if (this->expr_left->dataType.type != DataType::class_) {
                throw Exception(Exception::TYPE_ERROR,
                                this->expr_left->dataType.toString() + " has not fields", this->line);
            }

            try {
                FieldTableItem fieldItem = ClassTable::Instance()->getField(this->expr_left->dataType.id, *this->Name);
                this->dataType = fieldItem.dataType;
                this->isConst = this->expr_left->isConst || fieldItem.isConst;
                this->isMut = this->expr_left->isMut && !fieldItem.isConst;
                if (fieldItem.isConst) {
                    throw Exception(Exception::STATIC_ERROR,
                                    this->expr_left->dataType.id + " " + *this->Name + "is static field", this->line);
                }

                if (!ClassTable::isHaveAccessToField(curClassName, this->expr_left->dataType.id, *this->Name)) {
                    throw Exception(Exception::ACCESS_ERROR, curClassName + " not has access to field " + *this->Name,
                                    this->line);
                }

//                ClassTable::addFieldRefToConstTable(curClassName, this->expr_left->dataType.id, *this->Name,
//                                                    ClassTable::Instance()->getField(this->expr_left->dataType.id,
//                                                                                     *this->Name).dataType);
            }
            catch (Exception e) {
                throw e;
            }

            this->localVarNum = expr_left->localVarNum;
            this->fieldName = expr_left->fieldName;

            break;
        case method_expr:
            addMetaInfo(this->expr_left);
            checkCancelExprNode(this->expr_left);
            if (this->expr_list != NULL) {
                addMetaInfo(this->expr_list);
            }
            this->expr_left->transform(isConvertedToConst);


            if (this->expr_left->dataType.isString()) {
                auto exprNode = ExprNode::CallAccessExpr(ExprNode::id_, this->Name, NULL, NULL);
                auto firstParam = this->expr_left;

                this->type = static_method;
                this->expr_left = exprNode;
                this->expr_list->exprs->push_front(firstParam);
                this->transform();
                return;
            }

            if (this->expr_left->dataType.type != DataType::class_) {
                throw Exception(Exception::TYPE_ERROR,
                                this->expr_left->dataType.toString() + "has not methods", this->line);
            }

            try {

                MethodTableItem methodItem = ClassTable::Instance()->getMethodDeep(this->expr_left->dataType.id,
                                                                                   *this->Name);
                if (methodItem.isStatic) {
                    throw Exception(Exception::STATIC_ERROR,
                                    this->expr_left->dataType.id + " " + *this->Name + "is static method", this->line);
                }

                //VarTableItem selfVarItem = methodItem.localVarTable.getVar(0); ///TODO  пососи ебучая константа

                this->checkMethodParam(this->expr_left->dataType.id, *this->Name);
                this->dataType = methodItem.returnDataType;

                if (!ClassTable::isHaveAccessToMethtod(curClassName, this->expr_left->dataType.id, *this->Name)) {
                    throw Exception(Exception::ACCESS_ERROR, curClassName + " not has access to method " + *this->Name,
                                    this->line);
                }

                vector<DataType> params;

                for (auto elem: methodItem.paramTable.items) {
                    params.push_back(elem.dataType);
                }
                if (methodItem.isStatic == false) {
                    params.erase(params.begin());
                }
//                ClassTable::addMethodRefToConstTable(curClassName, this->expr_left->dataType.id, *this->Name, params,
//                                                     methodItem.returnDataType);
            }
            catch (Exception e) {
                throw e;
            }

            break;
        case break_with_val_expr:
            addMetaInfo(expr_left);
            checkCancelExprNode(this->expr_left);
            this->expr_left->transform(isConvertedToConst);
            breakTypes.push_back(this->expr_left->dataType);
            this->dataType = DataType(DataType::void_);
            if (loopCnt == 0) {
                throw Exception(Exception::LOOP_ERROR, "continue is loop outside", this->line);
            }

            break;
        case break_expr:
            //   addMetaInfo(expr_left);
            //  checkCancelExprNode(this->expr_left);
            breakTypes.push_back(DataType(DataType::void_));
            this->dataType = DataType(DataType::void_);
            if (loopCnt == 0) {
                throw Exception(Exception::LOOP_ERROR, "continue is loop outside", this->line);
            }
            break;
            break;
        case range_right:
            addMetaInfo(expr_left);
            this->expr_left->transform(isConvertedToConst);
            if (expr_left->dataType.type != DataType::int_) {
                throw Exception(Exception::TYPE_ERROR,
                                "range expr should be int_. Result: " + expr_left->dataType.toString(), this->line);
            }

            this->expr_right = this->expr_left;
            this->expr_left = ExprNode::ExprFromIntLiteral(int_lit, 0);
            this->expr_left->dataType = DataType(DataType::int_);
            this->type = range_expr;
            break;
        case range_left:
            addMetaInfo(expr_left);
            checkCancelExprNode(this->expr_left);
            this->expr_left->transform(isConvertedToConst);
            if (expr_left->dataType.type != DataType::int_) {
                throw Exception(Exception::TYPE_ERROR,
                                "range expr should be int_. Result: " + expr_left->dataType.toString(), this->line);
            }
            this->expr_right = ExprNode::ExprFromIntLiteral(int_lit, INT32_MAX);
            this->expr_right->dataType = DataType(DataType::int_);
            this->type = range_expr;
            break;
        case return_expr:

            if (this->expr_left == NULL) {
                returnTypes.push_back(DataType(DataType::void_));
            }

            addMetaInfo(expr_left);
            checkCancelExprNode(expr_left);
            this->expr_left->transform(isConvertedToConst);
            returnTypes.push_back(this->expr_left->dataType);
            this->dataType = DataType(DataType::void_);
            break;
        case if_expr_list: {
            vector<DataType> types;
            if (this->ifList != NULL) {
                for (auto elem: *this->ifList) {
                    addMetaInfo(elem);
                    // checkCancelExprNode(expr_left);
                    elem->transform(isConvertedToConst);
                    types.push_back(elem->dataType);
                }
            }

            if (this->else_body != NULL) {
                addMetaInfo(else_body);
                checkCancelExprNode(else_body);
                this->else_body->transform(isConvertedToConst);
                types.push_back(else_body->dataType);
            }

            if (!DataType::isEquals(types)) {
                throw Exception(Exception::TYPE_ERROR, "if has different types", this->line);
            }

            if (types.size())
                this->dataType = types.front();
            else
                this->dataType = DataType(DataType::void_);
        }
            break;
        case if_expr:
            addMetaInfo(expr_left);
            checkCancelExprNode(expr_left);
            this->expr_left->transform(isConvertedToConst);

            if (this->expr_left->dataType.type != DataType::bool_) {
                throw Exception(Exception::TYPE_ERROR,
                                "if condition expected: bool_, result: " +
                                this->expr_left->dataType.toString(), this->line);
            }

            addMetaInfo(body);
            checkCancelExprNode(body);
            this->body->transform(isConvertedToConst);
            this->dataType = this->body->dataType;
            break;
        case loop_expr:

            if (body->dataType.type == DataType::void_) {
                throw Exception(Exception::INCORRECT_TYPE, "loop_expr cannot has return_expr", this->line);
            }
            {
                addMetaInfo(body);
                vector<DataType> breaks = breakTypes;
                breakTypes.clear();
                loopCnt++;
                body->transform(isConvertedToConst);
                if (breakTypes.empty()) {
                    // throw Exception(Exception::LOOP_ERROR, "loop should has break", this->line);
                    this->dataType = DataType(DataType::void_);
                } else {
                    if (!DataType::isEquals(breakTypes)) {
                        throw Exception(Exception::TYPE_ERROR, "loop has different types", this->line);
                    }
                    this->dataType = breakTypes.front();
                    breakTypes = breaks;
                }

                loopCnt--;
            }


            break;
        case loop_while:

            addMetaInfo(expr_left);
            checkCancelExprNode(expr_left);
            this->expr_left->transform(isConvertedToConst);

            if (this->expr_left->dataType.type != DataType::bool_) {
                throw Exception(Exception::TYPE_ERROR,
                                "if condition expected: bool_, result: " +
                                this->expr_left->dataType.toString(), this->line);
            }


            {
                addMetaInfo(body);
                vector<DataType> breaks = breakTypes;
                breakTypes.clear();
                loopCnt++;
                body->transform(isConvertedToConst);
                breakTypes.push_back(DataType(DataType::void_));
                if (!DataType::isEquals(breakTypes)) {
                    throw Exception(Exception::TYPE_ERROR, "while should return void", this->line);
                }
                loopCnt--;
                breakTypes = breaks;
            }

            if (body->dataType.type != DataType::void_) {
                throw Exception(Exception::INCORRECT_TYPE, "while expr cannot has return_expr", this->line);
            }

            this->dataType = body->dataType;
            break;
        case loop_for:

            addMetaInfo(expr_left); // for ID IN Expr array 1.. {}
            //checkCancelExprNode(expr_left);
            this->expr_left->transform(isConvertedToConst);
            if (this->expr_left->type == break_expr || this->expr_left->type == return_expr
                || this->expr_left->type == break_with_val_expr) {
                throw Exception(Exception::TYPE_ERROR,
                                "Олег Александрович, ну че вы так  проверяете, не надо пожалуйста. У меня дети есть",
                                this->line);
            }

            if (this->expr_left->dataType.type != DataType::array_ &&
                this->expr_left->type != ExprNode::range_expr) {
                throw Exception(Exception::TYPE_ERROR,
                                "for condition should be iterable: range_expr or DataType::array_", this->line);
            }

            {
                DataType dataType = DataType(DataType::int_);
                if (this->expr_left->dataType.type == DataType::array_) {
                    dataType = this->expr_left->dataType.getArrDataType();
                }

                VarTableItem varItem = VarTableItem(*this->Name, dataType,
                                                    this->expr_left->isMut && this->expr_left->isRefExpr(),
                                                    false, true, false, body);

                this->loopCounterVar = ClassTable::addLoopCounterVar(curClassName, curMethodName);
                ClassTable::Instance()->addLocalParam(curClassName, curMethodName, varItem);
            }

            {
                auto classTable = *ClassTable::Instance();
            }
            if (this->expr_left->isRefExpr() == false && this->expr_left->isVar()) {
                ExprNode *delExpr = ExprNode::DelObjectExpr(this->expr_left);
                this->deleteExprList = new ExprListNode(delExpr);
            }

//            if (this->expr_left->isRefExpr() && this->expr_left->dataType.type == DataType::array_ &&
//                this->expr_left->dataType.arrDeep == 1 && this->expr_left->dataType.getArrDataType().isSimple()) {
//                throw Exception(Exception::NOT_SUPPORT,
//                                this->expr_left->dataType.toString() + " not support link operation", this->line);
//            }

            {
                addMetaInfo(body);
                vector<DataType> breaks = breakTypes;
                breakTypes.clear();
                loopCnt++;
                this->body->transform(isConvertedToConst);

                if (this->body->dataType.type != DataType::void_) {
                    throw Exception(Exception::TYPE_ERROR,
                                    "for condition should be iterable: range_expr or DataType::array_", this->line);
                }

                breakTypes.push_back(DataType(DataType::void_));
                if (!DataType::isEquals(breakTypes)) {
                    throw Exception(Exception::TYPE_ERROR, "breaks should be void_ in for", this->line);
                }
                loopCnt--;
                breakTypes = breaks;
            }

            this->dataType = body->dataType;
            break;
        case block_expr:

            blockExprList.push_back(this);
            if (this->stmt_list != NULL && this->stmt_list->stmts->size()) {
                int cur = 0;
                for (auto it = this->stmt_list->stmts->begin(); it != this->stmt_list->stmts->end(); it++) {
                    auto elem = *it;
                    elem->curClassName = curClassName;
                    elem->curMethodName = curMethodName;
                    elem->transform(isConvertedToConst);

                    if (elem->type == StmtNode::exprstmt) {
                        if ((elem->expr->type == loop_expr ||
                             elem->expr->type == ExprNode::if_expr_list) &&
                            elem->expr->dataType.type != DataType::void_) {

                            if (elem == this->stmt_list->stmts->back() && this->body != NULL) {
                                throw Exception(Exception::TYPE_ERROR,
                                                "if or loop without  semicolon should return  void_. Result: " +
                                                elem->expr->dataType.toString(), elem->line);
                            }

                            if (elem != this->stmt_list->stmts->back()) {

                                StmtNode *nextElem = *(std::next(it, 1));

                                if (nextElem->type != StmtNode::semicolon) {
                                    throw Exception(Exception::TYPE_ERROR,
                                                    "if or loop without  semicolon should return  void_. result: " +
                                                    elem->expr->dataType.toString(), elem->line);
                                }

                            }

                        }

                    }


                }
            }


            if (this->body == NULL && this->stmt_list != NULL && this->stmt_list->stmts->size()) {
                auto last_stmt = this->stmt_list->stmts->back();
                if (last_stmt->type == StmtNode::exprstmt &&
                    (last_stmt->expr->type == ExprNode::loop_expr ||
                     (last_stmt->expr->type == ExprNode::if_expr_list))) {
                    this->dataType = last_stmt->expr->dataType;
                    this->body = last_stmt->expr;
                    this->stmt_list->stmts->pop_back();
                }
            } else if (this->body != NULL) {
                addMetaInfo(body);
                this->body->transform(isConvertedToConst);
            }

            if (this->body != NULL) {
                this->dataType = this->body->dataType;
            } else {

                DataType bodyDataType = DataType(DataType::void_);
                bool isStmtsNotEmpty = this->stmt_list != NULL && this->stmt_list->stmts->size();
                bool isExpr = isStmtsNotEmpty && this->stmt_list->stmts->back()->type == StmtNode::exprstmt;
                bool isReturn = isExpr && this->stmt_list->stmts->back()->expr->type == ExprNode::return_expr;
                bool isMethodBody = this == ClassTable::Instance()->getMethod(curClassName, curMethodName).body;
                if (isReturn && isMethodBody) {
                    auto returnExpr = this->stmt_list->stmts->back()->expr;
                    if (returnExpr->expr_left != NULL) {
                        bodyDataType = returnExpr->expr_left->dataType;
                    }
                }

                this->dataType = bodyDataType;
            }

            blockExprList.pop_back();
            break;

        case struct_expr:
            break;
        case struct_field_expr:
            /* empty */
            break;
        case static_method:
            addMetaInfo(this->expr_left);
            checkCancelExprNode(this->expr_left);
            this->expr_left->transformPathCallExpr(curClassName, ExprNode::static_method, false);
            this->expr_middle = ExprNode::CallAccessExpr(ExprNode::id_, new string(expr_left->methodName), NULL, NULL);

            if (ClassTable::isMethodExistDeep(this->expr_left->className, *this->expr_middle->Name)) {
                this->dataType = ClassTable::getMethodDeep(this->expr_left->className,
                                                           *this->expr_middle->Name).returnDataType;
            } else if (ClassTable::Instance()->isMethodExist(ClassTable::RTLClassName, *this->expr_middle->Name)) {
                this->expr_left->className = ClassTable::RTLClassName;
                this->dataType = ClassTable::Instance()->getMethod(this->expr_left->className,
                                                                   *this->expr_middle->Name).returnDataType;
            } else {
                throw Exception(Exception::NOT_EXIST,
                                "call method " + this->expr_left->className + " " + *this->expr_left->Name +
                                " not exist", this->line);
            }

            checkMethodParam(this->expr_left->className, this->expr_left->methodName);
            if (!ClassTable::isHaveAccess(curClassName, this->expr_left->className)) {
                throw Exception(Exception::ACCESS_ERROR,
                                curClassName + " has not access to " + this->expr_left->className, this->line);
            }

            if (ClassTable::Instance()->getClass(this->expr_left->className).classType == ClassTableItem::trait_ &&
                curClassName != this->expr_left->className) {
                throw Exception(Exception::ACCESS_ERROR,
                                this->expr_left->className + " is trait and you cannot call " +
                                *this->expr_middle->Name, this->line);
            }

            if (curClassName == ConstTable::globalClassName + "/" + ConstTable::moduleClassName) {
                int x = 10 + 11;
            }

            if (!ClassTable::isHaveAccessToMethtod(curClassName, this->expr_left->className,
                                                   *this->expr_middle->Name)) {
                throw Exception(Exception::ACCESS_ERROR,
                                curClassName + " has not access to " + *this->expr_middle->Name, this->line);
            }

            {
                vector<DataType> params;
                MethodTableItem methodTableItem = ClassTable::getMethodDeep(this->expr_left->className,
                                                                            *this->expr_middle->Name);

                if (methodTableItem.isStatic == false) {
                    throw Exception(Exception::TYPE_ERROR,
                                    *this->expr_middle->Name + " in class " + className + " is not static", this->line);
                }

//                ClassTable::addMethodRefToConstTable(curClassName, this->expr_left->className, *this->expr_middle->Name,
//                                                     params,
//                                                     methodTableItem.returnDataType);
            }
            break;
        case path_call_expr:
            addMetaInfo(this->expr_left);
            checkCancelExprNode(this->expr_left);

            this->transformPathCallExpr(curClassName, ExprNode::field_access_expr, false);
            this->expr_middle = ExprNode::CallAccessExpr(ExprNode::id_, new string(fieldName), NULL, NULL);

            if (ClassTable::isFieldExistDeep(this->className, *this->expr_middle->Name)) {
                this->dataType = ClassTable::getFieldDeep(this->className,
                                                          *this->expr_middle->Name).dataType;
            } else {
                throw Exception(Exception::NOT_EXIST,
                                "call field " + this->expr_left->className + " " + *this->Name +
                                " not exist", this->line);
            }

            if (ClassTable::Instance()->getClass(this->expr_left->className).classType == ClassTableItem::trait_ &&
                curClassName != this->expr_left->className) {
                throw Exception(Exception::ACCESS_ERROR,
                                this->expr_left->className + " is trait and you cannot call " +
                                *this->expr_middle->Name, this->line);
            }

            break;

        case struct_creation:
            this->checkStructExpr();
            break;
        case as:
            addMetaInfo(this->expr_left);
            checkCancelExprNode(this->expr_left);
            this->expr_left->transform(isConvertedToConst);
            if (DataType::isCanConvert(this->expr_left->dataType, this->typeNode->convertToDataType(curClassName))) {
                this->dataType = this->typeNode->convertToDataType(curClassName);
            } else {
                throw Exception(Exception::TYPE_ERROR,
                                "cannot convert type " + this->expr_left->dataType.toString() + " to " +
                                this->typeNode->convertToDataType(curClassName).toString(), this->line);
            }


            break;

        case id_: {
            int tmp = Node::getVarNumber(blockExprList, curClassName, curMethodName, *this->Name);
            if (tmp != -1) {
                this->localVarNum = tmp;
                VarTableItem varItem = ClassTable::Instance()->getLocalVar(curClassName, curMethodName, tmp);
                this->isMut = varItem.isMut;
                this->isConst = varItem.isConst;
                this->dataType = varItem.dataType;
            } else if (ClassTable::Instance()->isFieldExist(curClassName, *this->Name)) {
                this->fieldName = *this->Name;
                FieldTableItem fieldItem = ClassTable::Instance()->getField(curClassName, *this->Name);
                this->isMut = !fieldItem.isConst;
                this->isConst = fieldItem.isConst;
                this->dataType = fieldItem.dataType;
            } else {
                throw Exception(Exception::NOT_EXIST, "var " + *this->Name + " not exist", this->line);
            }

        }
            break;
        case self_expr: {
            MethodTableItem methodItem = ClassTable::Instance()->getMethod(curClassName, curMethodName);

            if (methodItem.isStatic) {
                throw Exception(Exception::STATIC_ERROR, "static error: self used in static method ", this->line);
            }

            this->localVarNum = 0; //TODO бебебе
            this->dataType = methodItem.paramTable.getVar(0).dataType;
            this->isMut = methodItem.paramTable.getVar(0).isMut;
        }
            break;
        case super_expr:
            throw Exception(Exception::NOT_SUPPORT, "here are too many leading `super` keywords", this->line);
            break;


        case int_lit:
            this->dataType = DataType(DataType::int_);
            if (this->Int < INT16_MIN || this->Int > INT16_MAX) {
//                ClassTable::addIntToConstTable(curClassName, this->Int);
            }
            this->isConst = true;
            break;
        case float_lit:
            this->dataType = DataType(DataType::float_);
//            ClassTable::addFloatToConstTable(curClassName, this->Float);
            this->isConst = true;
            break;
        case char_lit:
            this->dataType = DataType(DataType::char_);
            this->isConst = true;
            break;
        case string_lit:
            this->dataType = DataType(DataType::string_);
//            ClassTable::addStringToConstTable(curClassName, *this->String);
            this->isConst = true;
            break;
        case raw_string_lit:
            this->dataType = DataType(DataType::string_);
//            ClassTable::addStringToConstTable(curClassName, *this->String);
            this->isConst = true;
            break;
        case bool_lit:
            this->dataType = DataType(DataType::bool_);
            this->isConst = true;
            break;

        case question:
        case ustar:
        case tuple_expr:
            throw Exception(Exception::NOT_SUPPORT, "this operation not supported", this->line);
            break;

        case link:
            addMetaInfo(this->expr_left);
            checkCancelExprNode(this->expr_left);
            this->expr_left->transform(isConvertedToConst);
            if (this->expr_left->isVar() == false) {
                throw Exception(Exception::UNEXPECTED, "link operation with not var element", this->line);
            }

            this->dataType = this->expr_left->dataType;
            this->isMut = false;
            this->localVarNum = this->expr_left->isVar();
            this->fieldName = this->expr_left->fieldName;

            if (this->dataType.isSimple()) {
                throw Exception(Exception::NOT_SUPPORT, "operation mut_link not support with simple type", this->line);
            }

            break;
        case mut_link:

            addMetaInfo(this->expr_left);
            checkCancelExprNode(this->expr_left);
            this->expr_left->transform(isConvertedToConst);

            if (this->expr_left->isVar() == false) {
                throw Exception(Exception::UNEXPECTED, "link operation with not var element", this->line);
            }

            if (this->expr_left->isMut == false) {
                throw Exception(Exception::UNEXPECTED, "Cannot create mut link element because var is not mut",
                                this->line);
            }

            this->dataType = this->expr_left->dataType;
            this->localVarNum = this->expr_left->isVar();
            this->fieldName = this->expr_left->fieldName;
            this->isMut = true;

            if (this->dataType.isSimple()) {
                throw Exception(Exception::NOT_SUPPORT, "operation mut_link not support with simple type", this->line);
            }
            break;


        case call_expr:
        case continue_expr:
            if (loopCnt == 0) {
                throw Exception(Exception::LOOP_ERROR, "continue is loop outside", this->line);
            }
            break;
    }

}

void ExprNode::transformConst() {


    switch (this->type) {
        case plus:
        case minus:
        case mul_expr:
        case div_expr:
        case mod:
//        case or_:
//        case and_:
        case asign:
        case equal:
        case not_equal:
        case greater:
        case less:
        case greater_equal:
        case less_equal:
            this->expr_left->transformConst();
            this->expr_right->transformConst();
            if (!this->expr_left->isEqualDataType(this->expr_right)) {
                throw Exception(Exception::NOT_EQUAL_DATA_TYPE,
                                "NOT EQUAL DATATYPE " + this->expr_left->dataType.toString() + " and" +
                                this->expr_right->dataType.toString(), this->line);
            }
            if (!this->expr_left->isLiteral() || !this->expr_right->isLiteral()) {
                throw Exception(Exception::NOT_CONST, "Excepted CONST but it NOT CONST", this->line);
            }
            break;
        case uminus:
        case negotation:
        case as:
            this->expr_left->transformConst();
            if (!this->expr_left->isLiteral()) {
                throw Exception(Exception::NOT_CONST, "Excepted CONST but it NOT CONST", this->line);
            }
            break;
    }

    switch (this->type) {

        case plus:
            if (this->expr_left->dataType.type == DataType::int_) {
                this->Int = this->expr_left->Int + this->expr_right->Int;
                this->type = int_lit;
            } else if (this->expr_left->dataType.type == DataType::float_) {
                this->Float = this->expr_left->Float + this->expr_right->Float;
                this->type = float_lit;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION",
                                this->line);
            }

            this->dataType.type = this->expr_left->dataType.type;
            break;
        case minus:
            if (this->expr_left->dataType.type == DataType::int_) {
                this->Int = this->expr_left->Int - this->expr_right->Int;
                this->type = int_lit;
            } else if (this->expr_left->dataType.type == DataType::float_) {
                this->Float = this->expr_left->Float - this->expr_right->Float;
                this->type = float_lit;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION",
                                this->line);
            }

            this->dataType.type = this->expr_left->dataType.type;
            break;
        case mul_expr:
            if (this->expr_left->dataType.type == DataType::int_) {
                this->Int = this->expr_left->Int * this->expr_right->Int;
                this->type = int_lit;
            } else if (this->expr_left->dataType.type == DataType::float_) {
                this->Float = this->expr_left->Float * this->expr_right->Float;
                this->type = float_lit;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION",
                                this->line);
            }

            this->dataType.type = this->expr_left->dataType.type;
            break;
        case div_expr:
            if (this->expr_left->dataType.type == DataType::int_) {
                if (this->expr_right->Int == 0) {
                    throw Exception(Exception::NULL_DIVIDE, "NULL DIVIDE", this->line);
                }
                this->Int = this->expr_left->Int / this->expr_right->Int;
                this->type = int_lit;
            } else if (this->expr_left->dataType.type == DataType::float_) {
                if (this->expr_right->Float == 0) {
                    throw Exception(Exception::NULL_DIVIDE, "NULL DIVIDE", this->line);
                }
                this->Float = this->expr_left->Float / this->expr_right->Float;
                this->type = float_lit;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION",
                                this->line);
            }

            this->dataType.type = this->expr_left->dataType.type;
            break;
        case mod:
            if (this->expr_left->dataType.type == DataType::int_) {
                if (this->expr_right->Int == 0) {
                    throw Exception(Exception::NULL_DIVIDE, "NULL DIVIDE", this->line);
                }
                this->Int = this->expr_left->Int % this->expr_right->Int;
                this->type = int_lit;
            } else if (this->expr_left->dataType.type == DataType::float_) {
                if (this->expr_right->Float == 0) {
                    throw Exception(Exception::NULL_DIVIDE, "NULL DIVIDE", this->line);
                }
                this->Float = fmodf(this->expr_left->Float,this->expr_right->Float);
                this->type = float_lit;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION",
                                this->line);
            }

            this->dataType.type = this->expr_left->dataType.type;
            break;
        case or_:
            this->expr_left->transformConst();
            if (this->expr_left->dataType.type == DataType::bool_) {

                if (!this->expr_left->isLiteral()) {
                    throw Exception(Exception::NOT_CONST, "Excepted CONST but it NOT CONST", this->line);
                }

                if (this->expr_left->Bool == 1) {
                    this->Bool = 1;
                } else {
                    this->expr_right->transformConst();

                    if (!this->expr_right->isLiteral()) {
                        throw Exception(Exception::NOT_CONST, "Excepted CONST but it NOT CONST", this->line);
                    }

                    if (this->expr_right->dataType.type == DataType::bool_) {
                        this->Bool = this->expr_right->Bool;
                    } else {
                        throw Exception(Exception::OPERATION_NOT_SUPPORTED,
                                        "THIS LITERAL NOT SUPPORTED THIS OPERATION. RIGHT OPERAND ARE NOT BOOL",
                                        this->line);
                    }

                }
                //this->Bool = this->expr_left->Bool || this->expr_right->Bool;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION - OR",
                                this->line);
            }

            this->type = bool_lit;
            this->dataType.type = this->expr_left->dataType.type;
            break;
        case and_:
            this->expr_left->transformConst();
            if (!this->expr_left->isLiteral()) {
                throw Exception(Exception::NOT_CONST, "Excepted CONST but it NOT CONST", this->line);
            }
            if (this->expr_left->dataType.type == DataType::bool_) {
                if (this->expr_left->Bool == 0) {
                    this->Bool = 0;
                } else {
                    this->expr_right->transformConst();

                    if (!this->expr_right->isLiteral()) {
                        throw Exception(Exception::NOT_CONST, "Excepted CONST but it NOT CONST", this->line);
                    }

                    if (this->expr_right->dataType.type == DataType::bool_) {
                        this->Bool = this->expr_right->Bool;
                    } else {
                        throw Exception(Exception::OPERATION_NOT_SUPPORTED,
                                        "THIS LITERAL NOT SUPPORTED THIS OPERATION. RIGHT OPERAND ARE NOT BOOL",
                                        this->line);
                    }
                }
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION - AND",
                                this->line);
            }

            this->type = bool_lit;
            this->dataType.type = this->expr_left->dataType.type;
            break;
        case equal:
            if (this->expr_left->dataType.type == DataType::bool_) {
                this->Bool = this->expr_left->Bool == this->expr_right->Bool;
            } else if (this->expr_left->dataType.type == DataType::int_) {
                this->Bool = this->expr_left->Int == this->expr_right->Int;
            } else if (this->expr_left->dataType.type == DataType::float_) {
                this->Bool = this->expr_left->Float == this->expr_right->Float;
            } else if (this->expr_left->dataType.type == DataType::char_) {
                this->Bool = this->expr_left->Char == this->expr_right->Char;
            } else if (this->expr_left->dataType.type == DataType::string_) {
                this->Bool = *this->expr_left->String == *this->expr_right->String;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION",
                                this->line);
            }

            this->type = bool_lit;
            this->dataType.type = DataType::bool_;

            break;
        case not_equal:
            if (this->expr_left->dataType.type == DataType::bool_) {
                this->Bool = this->expr_left->Bool != this->expr_right->Bool;
            } else if (this->expr_left->dataType.type == DataType::int_) {
                this->Bool = this->expr_left->Int != this->expr_right->Int;
            } else if (this->expr_left->dataType.type == DataType::float_) {
                this->Bool = this->expr_left->Float != this->expr_right->Float;
            } else if (this->expr_left->dataType.type == DataType::char_) {
                this->Bool = this->expr_left->Char != this->expr_right->Char;
            } else if (this->expr_left->dataType.type == DataType::string_) {
                this->Bool = *this->expr_left->String != *this->expr_right->String;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION",
                                this->line);
            }
            this->type = bool_lit;
            this->dataType.type = DataType::bool_;
            break;
        case greater:
            if (this->expr_left->dataType.type == DataType::bool_) {
                this->Bool = this->expr_left->Bool > this->expr_right->Bool;
            } else if (this->expr_left->dataType.type == DataType::int_) {
                this->Bool = this->expr_left->Int > this->expr_right->Int;
            } else if (this->expr_left->dataType.type == DataType::float_) {
                this->Bool = this->expr_left->Float > this->expr_right->Float;
            } else if (this->expr_left->dataType.type == DataType::char_) {
                this->Bool = this->expr_left->Char > this->expr_right->Char;
            } else if (this->expr_left->dataType.type == DataType::string_) {
                this->Bool = *this->expr_left->String > *this->expr_right->String;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION",
                                this->line);
            }

            this->type = bool_lit;
            this->dataType.type = DataType::bool_;
            break;
        case less:
            if (this->expr_left->dataType.type == DataType::bool_) {
                this->Bool = this->expr_left->Bool < this->expr_right->Bool;
            } else if (this->expr_left->dataType.type == DataType::int_) {
                this->Bool = this->expr_left->Int < this->expr_right->Int;
            } else if (this->expr_left->dataType.type == DataType::float_) { // 1 + 1 * 3 = 4
                this->Bool = this->expr_left->Float < this->expr_right->Float;
            } else if (this->expr_left->dataType.type == DataType::char_) {
                this->Bool = this->expr_left->Char < this->expr_right->Char;
            } else if (this->expr_left->dataType.type == DataType::string_) {
                this->Bool = *this->expr_left->String < *this->expr_right->String;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION",
                                this->line);
            }
            this->type = bool_lit;
            this->dataType.type = DataType::bool_;
            break;
        case greater_equal:
            if (this->expr_left->dataType.type == DataType::bool_) {
                this->Bool = this->expr_left->Bool >= this->expr_right->Bool;
            } else if (this->expr_left->dataType.type == DataType::int_) {
                this->Bool = this->expr_left->Int >= this->expr_right->Int;
            } else if (this->expr_left->dataType.type == DataType::float_) {
                this->Bool = this->expr_left->Float >= this->expr_right->Float;
            } else if (this->expr_left->dataType.type == DataType::char_) {
                this->Bool = this->expr_left->Char >= this->expr_right->Char;
            } else if (this->expr_left->dataType.type == DataType::string_) {
                this->Bool = *this->expr_left->String >= *this->expr_right->String;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION",
                                this->line);
            }
            this->type = bool_lit;
            this->dataType.type = DataType::bool_;

            break;
        case less_equal:
            if (this->expr_left->dataType.type == DataType::bool_) {
                this->Bool = this->expr_left->Bool <= this->expr_right->Bool;
            } else if (this->expr_left->dataType.type == DataType::int_) {
                this->Bool = this->expr_left->Int <= this->expr_right->Int;
            } else if (this->expr_left->dataType.type == DataType::float_) {
                this->Bool = this->expr_left->Float <= this->expr_right->Float;
            } else if (this->expr_left->dataType.type == DataType::char_) {
                this->Bool = this->expr_left->Char <= this->expr_right->Char;
            } else if (this->expr_left->dataType.type == DataType::string_) {
                this->Bool = *this->expr_left->String <= *this->expr_right->String;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION",
                                this->line);
            }

            this->type = bool_lit;
            this->dataType.type = DataType::bool_;
            break;
        case uminus:
            if (this->expr_left->dataType.type == DataType::int_) {
                this->Int = -this->expr_left->Int;
                this->type = int_lit;
            } else if (this->expr_left->dataType.type == DataType::float_) {
                this->Float = -this->expr_left->Float;
                this->type = float_lit;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION",
                                this->line);
            }
            this->dataType.type = this->expr_left->dataType.type;
            break;
        case negotation:
            if (this->expr_left->dataType.type == DataType::bool_) {
                this->Bool = !this->expr_left->Bool;
                this->type = bool_lit;
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION",
                                this->line);
            }

            this->dataType.type = DataType::bool_;
            break;
        case as:
            if (this->expr_left->dataType.type == DataType::int_) {
                switch (this->typeNode->dataType.type) {

                    case DataType::float_:
                        this->Float = this->expr_left->Int;
                        this->dataType.type = DataType::float_;
                        this->type = float_lit;
                        break;
                    case DataType::char_:
                        if (this->expr_left->Int > 255 || this->expr_left->Int < 0) {
                            throw Exception(Exception::CANNOT_CONVERTED, "Too long for char", this->line);
                        }
                        this->Char = this->expr_left->Int;
                        this->dataType.type = DataType::char_;
                        this->type = char_lit;
                        break;

                    case DataType::bool_:
                    case DataType::string_: // пусть явно будет а то дефолт еще фиг вспомнишь что так
                    case DataType::class_:
                    case DataType::array_:
                    case DataType::void_:
                        throw Exception(Exception::CANNOT_CONVERTED, "Cannot convert one type to other",
                                        this->line);
                        break;
                    case DataType::int_:
                        break;
                }
            } else if (this->expr_left->dataType.type == DataType::float_) {
                switch (this->typeNode->dataType.type) {

                    case DataType::int_:
                        this->Int = this->expr_left->Float;
                        this->dataType.type = DataType::int_;
                        this->type = int_lit;
                        break;
                    case DataType::char_:
                    case DataType::bool_:
                    case DataType::string_: // пусть явно будет а то дефолт еще фиг вспомнишь что так
                    case DataType::class_:
                    case DataType::array_:
                    case DataType::void_:
                        throw Exception(Exception::CANNOT_CONVERTED, "Cannot convert one type to other",
                                        this->line);
                        break;
                    case DataType::float_:
                        break;
                }
            } else if (this->expr_left->dataType.type == DataType::char_) {
                switch (this->typeNode->dataType.type) {

                    case DataType::int_:
                        this->Int = this->expr_left->Char;
                        this->dataType.type = DataType::int_;
                        this->type = int_lit;
                        break;

                    case DataType::char_:
                    case DataType::bool_:
                    case DataType::string_: // пусть явно будет а то дефолт еще фиг вспомнишь что так
                    case DataType::class_:
                    case DataType::array_:
                    case DataType::void_:
                        throw Exception(Exception::CANNOT_CONVERTED, "Cannot convert one type to other",
                                        this->line);
                        break;
                    case DataType::float_:
                        break;
                }
            } else {
                throw Exception(Exception::OPERATION_NOT_SUPPORTED, "THIS LITERAL NOT SUPPORTED THIS OPERATION",
                                this->line);
            }

            break;

        case question:
        case ustar:
        case link:
        case mut_link:
        case array_expr:
        case array_expr_auto_fill:
        case index_expr:
        case field_access_expr:
        case call_expr:
        case method_expr:
        case continue_expr:
        case break_expr:
        case break_with_val_expr:
        case return_expr:
        case self_expr:
        case if_expr_list:
        case if_expr:
        case loop_expr:
        case loop_while:
        case loop_for:
        case block_expr:
        case struct_expr:
        case struct_field_expr:
        case static_method:
        case tuple_expr:
        case super_expr:
        case path_call_expr:
        case add_if_block:
        case struct_creation:
        case undefined:
        case range_right: // надеюсь это говно тестить не будут а то лень реализовывать
        case range_left:
        case id_:
        case range_expr:
        case asign:
            throw Exception(Exception::NOT_LITERAL_OPERATION, "USED NOT LITERAL OPERATION");
            break;

        case int_lit:
            this->dataType.type = DataType::int_;
            break;
        case float_lit:
            this->dataType.type = DataType::float_;
            break;
        case char_lit:
            this->dataType.type = DataType::char_;
            break;
        case string_lit:
            this->dataType.type = DataType::string_;
            break;
        case raw_string_lit:
            this->dataType.type = DataType::string_;
            break;
        case bool_lit:
            this->dataType.type = DataType::bool_;
            break;

    }

    this->expr_left = NULL;
    this->expr_right = NULL;
}

void ExprNode::checkMethodParam(const string &className, const string &methodName) {

    try {
        MethodTableItem methodItem = ClassTable::Instance()->getMethodDeep(className,
                                                                           methodName);


        VarTable paramTable = methodItem.paramTable;

        if (!methodItem.isStatic) { //TODO это говно надо чекнуть
            paramTable.items.erase(paramTable.items.begin());
        }

        if (this->expr_list == NULL && paramTable.items.size() == 0) {
            return;
        }

        if (this->expr_list == NULL) {
            throw Exception(Exception::PARAM_ERROR,
                            "Param Error expected: " + to_string(paramTable.items.size())
                            + " param count result:" + to_string(0) + " param count", this->line);
        }

        if (this->expr_list->exprs->size() != paramTable.items.size()) {
            throw Exception(Exception::PARAM_ERROR,
                            "Param Error expected: " +
                            to_string(paramTable.items.size())
                            + " param count result:" + to_string(this->expr_list->exprs->size()) + " param count",
                            this->line);
        }

        int i = 0;
        for (auto elem: *this->expr_list->exprs) {
            addMetaInfo(elem);
            elem->transform();
            if (elem->type == ExprNode::break_with_val_expr || elem->type == ExprNode::break_expr ||
                elem->type == ExprNode::return_expr || elem->type == ExprNode::continue_expr) {
                throw Exception(Exception::TYPE_ERROR,
                                "Олег Александрович вы че куда суете. Какие брейки в параметрах. Жесть. 1984",
                                elem->line);
            }
            VarTableItem varItem = paramTable.items[i];
            bool isElemRef = varItem.isRef == elem->isRefExpr();
            bool isElemMut = !varItem.isMut || varItem.isMut == elem->isMut || (!elem->isRefExpr());
            bool isElemConst = !varItem.isConst || (!varItem.isMut && varItem.isConst == elem->isConst);
            bool checker = isElemMut && isElemRef && isElemConst;
            // bool checker = varItem.isRef == elem->isRefExpr() && varItem.isMut == elem->isMut && (varItem.isConst == elem->isConst || elem->isSimpleType());
            if (!varItem.dataType.isEquals(elem->dataType) &&
                !isParent(elem->dataType, varItem.dataType) || !checker) { //TODO проверить

                VarTableItem resultVarItem = VarTableItem(varItem.id, elem->dataType, elem->isMut, isRefExpr(),
                                                          true,
                                                          elem->isConst);
                throw Exception(Exception::TYPE_ERROR,
                                varItem.id + " type expected: " + varItem.toString() + " result: " +
                                resultVarItem.toString() + " ", this->line);
            }
            i++;

            if (!elem->isRefExpr() && elem->isVar() && !elem->dataType.isSimple()) {
                ExprNode *delExpr = ExprNode::DelObjectExpr(elem);

                if (this->deleteExprList == NULL) {
                    this->deleteExprList = new ExprListNode(delExpr);
                } else {
                    ExprListNode::Append(this->deleteExprList, delExpr);
                }
            }
        }
    }
    catch (Exception e) {
        throw e;
    }
}

void ExprNode::checkCancelExprNode(ExprNode *exprNode, bool isBreakCanceled) {

    if (exprNode->type == link) {
        throw Exception(Exception::TYPE_ERROR, "operation not supported by link", this->line);
    }

    if (exprNode->type == mut_link) {
        throw Exception(Exception::TYPE_ERROR, "operation not supported by mut_link", this->line);
    }

    if (exprNode->type == return_expr) {
        throw Exception(Exception::TYPE_ERROR, "operation not supported by return_expr", this->line);
    }

    if (exprNode->type == break_with_val_expr && isBreakCanceled) {
        throw Exception(Exception::TYPE_ERROR, "operation not supported by break with expr", this->line);
    }

    if (exprNode->type == break_expr) {
        throw Exception(Exception::TYPE_ERROR, "operation not supported by break", this->line);
    }

    if (exprNode->type == continue_expr) {
        throw Exception(Exception::TYPE_ERROR, "operation not supported by continue", this->line);
    }
}

bool ExprNode::isRefExpr() {
    return this->type == link || this->type == mut_link || this->dataType.type == DataType::string_;
}

bool ExprNode::isVar() {
    return this->localVarNum != -1 || this->fieldName.empty() == false;
}

void ExprNode::checkStructExpr(bool isConvertedTransform) {

    try {
        if (this->expr_left->type != path_call_expr && this->expr_left->type != id_) {
            throw Exception(Exception::CONSTRUCTOR_ERROR, "expression should be pathCallExpr", this->line);
        }


        this->expr_left->transformPathCallExpr(curClassName, undefined, true);
        this->className = this->expr_left->className;

        if (ClassTable::Instance()->getClass(this->className).classType != ClassTableItem::struct_) {
            throw Exception(Exception::TYPE_ERROR, "constructor error: " + className + " is not struct",
                            this->line);
        }

        int fieldSize = ClassTable::getStructFieldCount(className);

        if (fieldSize != this->field_list->exprs->size()) {
            throw Exception(Exception::CONSTRUCTOR_ERROR,
                            "fields count in constructor not equal field count in struct " + className +
                            ". Expected: " + to_string(fieldSize) + " result: " +
                            to_string(this->field_list->exprs->size()), this->line);
        }

        if (!ClassTable::isHaveAccess(curClassName, this->className)) {
            throw Exception(Exception::ACCESS_ERROR,
                            curClassName + " has not access to " + this->expr_left->className,
                            this->line);
        }


        vector<DataType> params;

        for (auto elem: *this->field_list->exprs) {
            addMetaInfo(elem);
            addMetaInfo(elem->expr_left);
            checkCancelExprNode(elem->expr_left);
            elem->expr_left->transform(isConvertedTransform);
            if (ClassTable::Instance()->isFieldExist(className, *elem->Name)) {
                FieldTableItem fieldItem = ClassTable::Instance()->getField(className, *elem->Name);
                if (!ClassTable::isHaveAccessToField(curClassName, this->expr_left->className, *elem->Name)) {
                    throw Exception(Exception::ACCESS_ERROR,
                                    curClassName + " has not access to private " + *elem->Name, elem->line);
                }

                params.push_back(fieldItem.dataType);

                if (!fieldItem.dataType.isEquals(elem->expr_left->dataType) &&
                    !isParent(elem->expr_left->dataType, fieldItem.dataType)) {

                    throw Exception(Exception::TYPE_ERROR,
                                    *elem->Name + "field type should be " + fieldItem.toString() + " " +
                                    elem->expr_left->dataType.toString(), elem->line);
                }
            } else {
                throw Exception(Exception::CONSTRUCTOR_ERROR,
                                *elem->Name + " field not exist in struct " + className);
            }
        }

//
//        ClassTable::addMethodRefToConstTable(curClassName, this->expr_left->className, "<init>", vector<DataType>(),
//                                             DataType(DataType::void_));

        this->dataType = DataType::StructDataType(this->className);

    }
    catch (Exception e) {
        throw e;
    }
}

void ExprNode::transformStructExpr() {

    if (this->type != struct_creation) {
        return;
    }

    if (!this->expr_left->isPathCallExpr()) {

        if (this->expr_left->expr_right != NULL && this->expr_left->expr_right->isPathCallExpr()) {
            auto left = this->expr_left;

            auto pathCallExpr = this->expr_left->expr_right;
            this->expr_left = pathCallExpr;
            auto structCreation = this;
            left->expr_right = structCreation;
            this->expr_middle = left;
            return;
        }

        if (this->expr_left->expr_left != NULL && this->expr_left->expr_left->isPathCallExpr()) {
            auto left = this->expr_left;

            auto pathCallExpr = this->expr_left->expr_left;
            this->expr_left = pathCallExpr;
            auto structCreation = this;
            left->expr_left = structCreation;
            this->expr_middle = left;
            return;
        }
    }
}

bool ExprNode::isPathCallExpr() {
    return this->type == path_call_expr || this->type == id_;
}


bool Node::isEqualDataType(Node *node) {
    return this->dataType.type == node->dataType.type;
}

void Node::transform(bool isConvertedToConst) {

}

void Node::addMetaInfo(Node *node) {
    node->curClassName = this->curClassName;
    node->curMethodName = this->curMethodName;
}

bool Node::isParent(const DataType &child, DataType parent) {
    if (child.type != DataType::class_) {
        return false;
    }
    if (parent.type != DataType::class_) {
        return false;
    }

    return ClassTable::Instance()->isParent(child.id, parent.id);
}

int Node::getVarNumber(vector<ExprNode *> &blockExprList, const string &className, const string &methodName,
                       const string &varName) {
    int res = -1;
    int cur = blockExprList.size() - 1;
    while (res == -1 & cur >= 0) {
        if (ClassTable::Instance()->isLocalVarExist(className, methodName, varName, blockExprList[cur])) {
            res = ClassTable::Instance()->getMethod(className, methodName).localVarTable.getVarNumber(varName,
                                                                                                      blockExprList[cur]);
            break;
        }
        cur--;
    }
    return res;
}

void Node::convertEnumValue() {
    if (this->varTableItem.dataType.isClass()) {
        string className = this->varTableItem.dataType.id;
        if (ClassTable::isEnum(className)) {
            this->varTableItem.dataType = DataType(DataType::int_);
        }
    }
}

void Node::setLine(Node *node) {
    if (node != NULL) {
        this->line = node->line;
    } else if (!this->line) {
        this->line = LineNum::getLineNum();
    }
}

int Node::getVarNumber(ExprNode *blockExpr, const string &className, const string &methodName, const string &varName) {
    return ClassTable::Instance()->getMethod(className, methodName).localVarTable.getVarNumber(varName,
                                                                                               blockExpr);
}

bool Node::isEqualDataType(DataType one, DataType other) {

    bool isParent = true;

    if (one.isClass() && other.isClass()) {
        isParent = ClassTable::Instance()->isParent(one.id, other.id);
    }

    if (one.isArray() && other.isArray()) {
        DataType tmp = one;
        tmp.id = other.id;
        isParent = tmp.isEquals(other) && ClassTable::Instance()->isParent(one.id, other.id);
    }

    return isParent || one.isEquals(other);
}

