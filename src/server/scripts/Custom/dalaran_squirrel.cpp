/********************************************
*											*
*				WoW ALive					*
*		Dalaran Eichhörnchen Script			*
*											*
*********************************************/


#include "ScriptPCH.h"
#include "alive.h"

class npc_dalaran_squirrel : public CreatureScript
{
public:
    npc_dalaran_squirrel() : CreatureScript("npc_dalaran_squirrel") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_dalaran_squirrelAI (creature);
    }

    struct npc_dalaran_squirrelAI : public ScriptedAI
    {
		npc_dalaran_squirrelAI(Creature* c) : ScriptedAI(c), summons(c) {}

		Unit* attacker;
		SummonList summons;

		void Reset()
        {
			summons.DespawnAll();
		}

		void EnterCombat(Unit* /*who*/)
        {
			for(int i = 0; i < 19; i++)
				{
					me->SummonCreature(NPC_DALARAN_SQUIRREL_SUMMON, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
				}
		}

		void JustDied(Unit* /*victim*/)
        {
			me->Respawn();				
			me->CombatStart(attacker);
		}
		
		void JustSummoned(Creature* summon)
            {
				summons.Summon(summon);
				if(Unit* target = me->getVictim())
				{
					if(target->isTotem() || target ->isPet())
					{
						target = target->GetOwner();
					}
				summon->AI()->AttackStart(target);
				}
			}

		 void UpdateAI(const uint32 diff)
        {
			if (!UpdateVictim())
				return;
			
			if(Unit* target = me->getVictim())
			{
				if(target->isTotem() || target->isPet())
				{
					target = target->GetOwner();
				}
				attacker = target;
				DoMeleeAttackIfReady();
			}
		}
	};
};

void AddSC_dalaran_squirrel()
{
	new npc_dalaran_squirrel();
}