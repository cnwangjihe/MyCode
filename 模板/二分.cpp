l=FEASIBLE_VALUE;
r=IMPOSSIBLE_VALUE;
while (r-l>PRE)
{
	mid=(l+r)/2;
	if (OK(mid)) l=mid;
	else r=mid;
}
ans=l;
/*OR*/
l=IMPOSSIBLE_VALUE;
r=FEASIBLE_VALUE;
while (r-l>PRE)
{
	mid=(l+r)/2;
	if (OK(mid)) r=mid;
	else l=mid;
}
ans=r;