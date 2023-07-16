#modified from https://stackoverflow.com/a/14902564
import json

# put all the things that we don't want duplicated here (not including id, which is always checked)
potential_duplicates = ['DataName']

"""
Checks to make sure id key is not duplicated in json
"""
def dict_raise_on_duplicates(ordered_pairs):
    """Reject duplicate keys."""
    d = {}
    duplicates = set()
    for k, v in ordered_pairs:
        if k in d:
           duplicates.add(k)
           #raise ValueError("duplicate key: %r" % (k,))
        else:
           d[k] = v
    if len(duplicates) > 0:
        raise Exception(f'Error: There are duplicate keys: {duplicates}')

    return d

"""
gets duplicate values in list
"""
def get_duplicates_in_list(list_to_check):
    # https://stackoverflow.com/a/15155286
    return list(set([x for x in list_to_check if list_to_check.count(x) > 1]))


with open('canDef.json') as f:
    js = json.load(f, object_pairs_hook=dict_raise_on_duplicates) # gets which id is duplicated
    for potential_duplicate in potential_duplicates:
        # gets list of all values for given parameter. i.e for potential_duplicate = 'DataName' it will
        # look like ['DASH_HEART', 'NEUTRINO0_ALIVE', 'NEUTRINO1_ALIVE']
        all_data_names = list(map(lambda v: js[v][potential_duplicate], js.keys())) 
        duplicates = get_duplicates_in_list(all_data_names)
        if len(duplicates) > 0:
            raise Exception(f'Error: There are duplicate {potential_duplicate}: {duplicates}')
