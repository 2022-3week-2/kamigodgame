#pragma once

enum class Cond2 {
	FF,
	TF,
	FT,
	TT,
};

/*
�����������ǂ��Ȃ����ߔ񐄏��B
���bool�̑g�ݍ��킹��Ԃ��B
�p��F
switch(DoubleCond( isA, isB ))
{
	case Cond2::FF:
		break;
	
	case Cond2::TF:
		break;

	case Cond2::FT:
		break;

	case Cond2::TT:
		break;
}
*/
Cond2 DoubleCond(bool first, bool second);

