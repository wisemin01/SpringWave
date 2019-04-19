
// ������ ��� �ĵ� �ڵ��Դϴ�.

// �ùķ��̼� Ƚ��
constexpr int	iterationCount = 3;
// ������ �� ���� ���
constexpr float springConstant = 0.0095f;
// ���̽����� ( ������ �⺻ ���� ) �� ���� ���
constexpr float baselineConstant = 0.0095f;
// ���� ��� ( �� �ùķ��̼Ǹ��� ������ )
constexpr float dampingConstant = 0.98f;

for (int i = 0; i < iterationCount; i++)
{
	for (int n = 0; n < indiceCount; n++)
	{
		waterIndex& node = waterIndices[n];

		// �� ����
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

		// ������� ���� ����
		float depth_from_height = transform->position.y - node.y;

		// ����� ���� ���� ����.
		force_to_baseline = baselineConstant * depth_from_height;

		// ���������� ��忡 ������ ��
		force = force_from_left + force_from_right + force_to_baseline;

		// ����� ���ǵ�
		node.spd.y = dampingConstant * node.spd.y + (force / node.mass);

		// ���� ����� y��ǥ�� �����Ų��.
		node.y = node.y + node.spd.y;
	}
}