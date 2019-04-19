
// 스프링 방식 파도 코드입니다.

// 시뮬레이션 횟수
constexpr int	iterationCount = 3;
// 스프링 힘 전달 계수
constexpr float springConstant = 0.0095f;
// 베이스라인 ( 수면의 기본 높이 ) 힘 전달 계수
constexpr float baselineConstant = 0.0095f;
// 감속 계수 ( 매 시뮬레이션마다 곱해짐 )
constexpr float dampingConstant = 0.98f;

for (int i = 0; i < iterationCount; i++)
{
	for (int n = 0; n < indiceCount; n++)
	{
		waterIndex& node = waterIndices[n];

		// 힘 변수
		float force = 0;
		float force_from_left = 0;
		float force_from_right = 0;
		float force_to_baseline = 0;

		if (n == 0)
		{
			force_from_left = 0;
		}
		else
		{
			force_from_left = waterIndices[n - 1].y - node.y;
			force_from_left *= springConstant;
		}

		if (n == indiceCount - 1)
		{
			force_from_right = 0;
		}
		else
		{
			force_from_right = waterIndices[n + 1].y - node.y;
			force_from_right *= springConstant;
		}

		// 수면과의 높이 차이
		float depth_from_height = transform->position.y - node.y;

		// 계수를 곱해 힘을 얻어낸다.
		force_to_baseline = baselineConstant * depth_from_height;

		// 최종적으로 노드에 가해질 힘
		force = force_from_left + force_from_right + force_to_baseline;

		// 노드의 스피드
		node.spd.y = dampingConstant * node.spd.y + (force / node.mass);

		// 실제 노드의 y좌표에 적용시킨다.
		node.y = node.y + node.spd.y;
	}
}